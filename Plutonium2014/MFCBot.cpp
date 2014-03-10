#include "MFCBot.h"
// CSTDLIB
#include <math.h>
// WPILib
#include "WPILib.h"
#include "Commands/Command.h"
// Utils
#include "Utils/Logger.h"
#include "Utils/Actuators/StallableMotor.h"
// Backend
#include "CommandBase.h"
#include "Robotmap.h"
#include "Subsystems/Pterodactyl.h"
// Commands
#include "Commands/Shooter/Latches/WLatch.h"
#include "Commands/Autonomous/Autonomous.h"

MFCBot::MFCBot() {
	lw = NULL;
	dont = 0;
	robotState = NULL;
	chooser = NULL;
}

MFCBot::~MFCBot() {

}

void MFCBot::createAutonomi() {
	chooser = new SendableChooser();
	chooser->AddDefault("One Ball", Autonomous::createAutoBall(1, 0));
	chooser->AddObject("One Ball, Drive Back",
			Autonomous::createAutoBall(1, -10));
	chooser->AddObject("Two Ball", Autonomous::createAutoBall(2, 0));
	chooser->AddObject("Two Ball, Drive Back",
			Autonomous::createAutoBall(2, -10));
	chooser->AddObject("Three Ball", Autonomous::createAutoBall(3, 0));
	chooser->AddObject("Just Drive", Autonomous::createJustDrive(0));
	chooser->AddObject("Drive, Drive Back", Autonomous::createJustDrive(-10));
	chooser->AddObject("Blank", new Autonomous());
	SmartDashboard::PutData("Autonomous Modes", chooser);
}

void MFCBot::RobotInit() {
	CommandBase::init();
	lw = LiveWindow::GetInstance();
	CommandBase::oi->registerButtonListeners();
	createAutonomi();

	robotState = NetworkTable::GetTable("Robot");
}

void MFCBot::AutonomousInit() {
	Scheduler::GetInstance()->RemoveAll();
	((Command*) chooser->GetSelected())->Start();
}

void MFCBot::AutonomousPeriodic() {
	/*Scheduler::GetInstance()->Run();
	 WatchDog();
	 if (dont++ > 10) {
	 printf("Encoder Left: %f, Encoder Right: %f \n",
	 CommandBase::driveBase->getLeftEncoder()->GetDistance(),
	 CommandBase::driveBase->getRightEncoder()->GetDistance());
	 dont = 0;
	 }*/
}

void MFCBot::TeleopInit() {
	Scheduler::GetInstance()->RemoveAll();
	robotState->PutNumber("alliance",
			DriverStation::GetInstance()->GetAlliance());
}

void MFCBot::TeleopPeriodic() {
	SmartDashboard::PutData(Scheduler::GetInstance());
	Scheduler::GetInstance()->Run();
	WatchDog();
	StallableMotor::updateControllers();
	if (dont++ > 10) {
		{
			robotState->PutBoolean("jawsClosed",
					CommandBase::collector->getJawState());
			robotState->PutNumber("pterodactylAngle",
					CommandBase::pterodactyl->getAngle());
			robotState->PutBoolean("hasBall",
					CommandBase::collector->isBallDetected());
			robotState->PutNumber("collectorMotorState",
					CommandBase::collector->isPIDEnabled() ?
							(CommandBase::collector->isRollerStalled() ? 2 : 1) :
							0);
			robotState->PutBoolean("shooterWinchStalled",
					CommandBase::shooter->isShooterMotorStalled());
			robotState->PutNumber("shooterStrap",
					CommandBase::shooter->getTurns());
			robotState->PutBoolean("shooterLatched",
					CommandBase::shooter->isReallyDrawnBack());
			robotState->PutNumber("compressorState",
					CommandBase::pneumatics->isCompressorOn() ? 1 : 0);
			robotState->PutNumber("driveLeftState",
					fabs(CommandBase::driveBase->getMotorSpeed()) > 0 ? 1 : 0);
			robotState->PutNumber("driveRightState",
					fabs(CommandBase::driveBase->getMotorSpeed()) > 0 ? 1 : 0);
		}
		{
			SmartDashboard::PutNumber("Winch rate",
					CommandBase::shooter->getTurnRate());
			SmartDashboard::PutNumber("Winch position",
					CommandBase::shooter->getTurns());

			SmartDashboard::PutNumber("pteroangle",
					CommandBase::pterodactyl->getAngle());
			SmartDashboard::PutNumber("pterorate",
					CommandBase::pterodactyl->getRate());
			SmartDashboard::PutBoolean("Shooter Pattern Latched",
					CommandBase::shooter->isLatchedByPattern());
			SmartDashboard::PutBoolean("Shooter Promixity Latched",
					CommandBase::shooter->isLatchedByProximity());
			SmartDashboard::PutBoolean("Shooter Winch Latch",
					CommandBase::shooter->getWLatch());
			SmartDashboard::PutBoolean("Shooter Motor Stalled",
					CommandBase::shooter->isShooterMotorStalled());

			SmartDashboard::PutNumber("ShooterOUT",
					CommandBase::oi->getPowerAdjustment());
			SmartDashboard::PutNumber("AngleOUT",
					CommandBase::oi->getAngleAdjustment());
		}
		dont = 0;
	}
}

void MFCBot::DisabledInit() {
	Scheduler::GetInstance()->RemoveAll();
}

void MFCBot::TestInit() {
	Scheduler::GetInstance()->RemoveAll();
}

void MFCBot::TestPeriodic() {
	lw->Run();
	StallableMotor::updateControllers();
	if (dont++ > 10) {
		dont = 0; //This kills the bug
	}
	WatchDog();
}

void MFCBot::WatchDog() {
	if (CommandBase::shooter != NULL) {
		if (CommandBase::shooter->getWenchMotorSpeed()
				< 0&& CommandBase::shooter->getTurns()
				> SHOOTER_WENCH_POT_FULL_OUT) {CommandBase::shooter->setWenchMotor(0.0);
		Logger::log(Logger::kWarning, "Watchdog","Shooter motor over released!");
	}
	if (CommandBase::shooter->getWenchMotorSpeed() < 0
			&& CommandBase::shooter->getWLatch() == Shooter::kLatched) {
		CommandBase::shooter->setWenchMotor(0.0);
		Logger::log(Logger::kWarning, "Watchdog","Shooter motor released without pawl disengaged!");
	}
	if (CommandBase::shooter->getWenchMotorSpeed() > 0) {
		if (CommandBase::shooter->getTurns() < 0) {
			CommandBase::shooter->setWenchMotor(0.0);
			Logger::log(Logger::kWarning, "Watchdog","Shooter motor overdrawn sensed by potentiometer!");
		}
		if (CommandBase::shooter->getTurns()
				< SHOOTER_WENCH_POT_REVERSE_ALLOW) {
#if SHOOTER_LIMITSWITCH
				if (CommandBase::shooter->isLatchedByProximity()) {
					CommandBase::shooter->setWenchMotor(0.0);
					Logger::log(Logger::kWarning, "Watchdog","Shooter motor overdrawn sensed by proximity switch!");
				}
#endif
				if (CommandBase::shooter->isLatchedByPattern()) {
					CommandBase::shooter->setWenchMotor(0.0);
					Logger::log(Logger::kWarning, "Watchdog","Shooter motor overdrawn sensed by latch pattern!");
				}
			}
		}
		if (CommandBase::shooter->isShooterMotorStalled()/* && CommandBase::shooter->getTurns() > 0.125*/) {
			Command *running = CommandBase::shooter->GetCurrentCommand();
			if (running != NULL) {
				if (running->GetName().compare("WLatch_Latched") != 0) {
					printf(
							"Watchdog: Killed command %s due to shooter stall!\n",
							running->GetName().c_str());
					Scheduler::GetInstance()->Remove(running);
					Scheduler::GetInstance()->AddCommand(
							new WLatch(Shooter::kLatched));
				}
			}
		}
	}
}

START_ROBOT_CLASS(MFCBot)
;

