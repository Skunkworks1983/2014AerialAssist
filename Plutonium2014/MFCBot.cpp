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
#include "Commands/Shooter/PrepareShooter.h"
#include "Commands/Autonomous/AutoStupidDrive.h"

MFCBot::MFCBot() {
	lw = NULL;
	dont = 0;
	robotState = NULL;
	chooser = NULL;
	thingy = new Relay(2, 1);
}

MFCBot::~MFCBot() {

}

void MFCBot::createAutonomi() {
	chooser = new SendableChooser();
	chooser->AddDefault("This (Stupid Auto)", Autonomous::createDerpy());
	chooser->AddObject("Blank", new Autonomous());
	//	chooser->AddObject("One Ball", Autonomous::createAutoBall(1, 0));
	//	chooser->AddObject("One Ball, Drive Back", Autonomous::createAutoBall(1,
	//			-10));
	//	chooser->AddObject("Two Ball", Autonomous::createAutoBall(2, 0));
	//	chooser->AddObject("Two Ball, Drive Back", Autonomous::createAutoBall(2,
	//			-10));
	//	chooser->AddObject("Three Ball", Autonomous::createAutoBall(3, 0));
	//	chooser->AddObject("Just Drive", Autonomous::createJustDrive(0));
	//	chooser->AddObject("Drive, Drive Back", Autonomous::createJustDrive(-10));

	chooser->AddObject("Stupid Drive", new AutoStupidDrive(3.0,-.25));
	SmartDashboard::PutData("Auto Modes", chooser);
}

void MFCBot::RobotInit() {
	CommandBase::init();
	lw = LiveWindow::GetInstance();
	CommandBase::oi->registerButtonListeners();
	createAutonomi();

	SmartDashboard::PutData("Log Level", Logger::createLogLevelChooser());

	robotState = NetworkTable::GetTable("Robot");
}

void MFCBot::AutonomousInit() {
	Scheduler::GetInstance()->RemoveAll();
	Command *cmd = ((Command*) chooser->GetSelected());
	if (cmd!=NULL) {
		cmd->Start();
		printf("Starting AUTO: %s\n", cmd->GetName().c_str());
	}
	Logger::log(Logger::kInfo, "Main", "Autonomous Init");
}

void MFCBot::AutonomousPeriodic() {
	Scheduler::GetInstance()->Run();
	WatchDog();
	StallableMotor::updateControllers();
}

void MFCBot::TeleopInit() {
	Scheduler::GetInstance()->RemoveAll();
	robotState->PutNumber("alliance", DriverStation::GetInstance()->GetAlliance());
	Logger::log(Logger::kInfo, "Main", "Teleop Init");
}

void MFCBot::TeleopPeriodic() {
	SmartDashboard::PutData(Scheduler::GetInstance());
	Scheduler::GetInstance()->Run();
	WatchDog();
	StallableMotor::updateControllers();

	if (CommandBase::pterodactyl->isPIDFinished(true)) {
		trueTicks++;
	} else {
		trueTicks = 0;
	}
	thingy->Set(trueTicks>15 ? Relay::kForward : Relay::kOff);

	if (dont++> 10) {
		int verbosity= GET_INT(SMARTDASH_VERBOSITY);
		if (GET_BOOL(ROBOT_VISUALIZATION)) {
			robotState->PutBoolean("jawsClosed",
					CommandBase::collector->getJawState());
			robotState->PutNumber("pterodactylAngle",
					CommandBase::pterodactyl->getAngle());
			robotState->PutBoolean("hasBall",
					CommandBase::collector->isBallDetected());
			robotState->PutNumber(
					"collectorMotorState",
					CommandBase::collector->isPIDEnabled() ? (CommandBase::collector->isRollerStalled() ? 2
							: 1)
							: 0);
			robotState->PutBoolean("shooterWinchStalled",
					CommandBase::shooter->isShooterMotorStalled());
			robotState->PutNumber("shooterStrap",
					CommandBase::shooter->getTurns());
			robotState->PutBoolean("shooterLatched",
					CommandBase::shooter->isReallyDrawnBack());
			robotState->PutNumber("compressorState",
					CommandBase::pneumatics->isCompressorOn() ? 1 : 0);
			robotState->PutNumber("driveLeftState",
					fabs(CommandBase::driveBase->getMotorSpeed())> 0 ? 1 : 0);
			robotState->PutNumber("driveRightState",
					fabs(CommandBase::driveBase->getMotorSpeed())> 0 ? 1 : 0);
		}
		if (verbosity & 1) {
			SmartDashboard::PutBoolean("Has Ball",
					CommandBase::collector->isBallDetected());
			SmartDashboard::PutBoolean("Shooter Ready",
					CommandBase::shooter->isReallyDrawnBack()
							&& CommandBase::shooter->lastReleasePosition > 0.0);
			SmartDashboard::PutBoolean("Pterodactyl Ready",
					CommandBase::pterodactyl->isPIDFinished(true));
		}
		if (verbosity & 2) {
			SmartDashboard::PutNumber("Winch position",
					CommandBase::shooter->getTurns());

			SmartDashboard::PutNumber("pteroangle",
					CommandBase::pterodactyl->getAngle());
		}
		if (verbosity & 4) {
			SmartDashboard::PutNumber("Winch rate",
					CommandBase::shooter->getTurnRate());
			SmartDashboard::PutNumber("pterorate",
					CommandBase::pterodactyl->getRate());
			SmartDashboard::PutNumber("Collect Rate",
					CommandBase::collector->getRollerSpeed());
		}
		if (verbosity & 8) {
			SmartDashboard::PutBoolean("Shooter Raw Latch",
					CommandBase::shooter->getRawSLatch());
			SmartDashboard::PutBoolean("Shooter Raw Promixity",
					CommandBase::shooter->getRawProximity());
			SmartDashboard::PutBoolean("Shooter Pattern Latched",
					CommandBase::shooter->isLatchedByPattern());
			SmartDashboard::PutBoolean("Shooter Promixity Latched",
					CommandBase::shooter->isLatchedByProximity());
			SmartDashboard::PutBoolean("Shooter Winch Latch",
					CommandBase::shooter->getWLatch());
			SmartDashboard::PutBoolean("Shooter Motor Stalled",
					CommandBase::shooter->isShooterMotorStalled());
		}
		dont = 0;
	}
}

void MFCBot::DisabledInit() {
	Scheduler::GetInstance()->RemoveAll();

	DriverStationLCD::GetInstance()->Printf(DriverStationLCD::kUser_Line1, 1, "%s %s",__TIME__ , __DATE__);
	DriverStationLCD::GetInstance()->Printf(DriverStationLCD::kUser_Line2, 1, "Saturday");
	DriverStationLCD::GetInstance()->UpdateLCD();
}

void MFCBot::TestInit() {
	Scheduler::GetInstance()->RemoveAll();
}

void MFCBot::TestPeriodic() {
	lw->Run();
	StallableMotor::updateControllers();
	if (dont++> 10) {
		dont = 0; //This kills the bug
	}
	WatchDog();
}

void MFCBot::WatchDog() {
	if (CommandBase::shooter != NULL) {
		if (CommandBase::shooter->getWenchMotorSpeed() < 0
				&& CommandBase::shooter->getTurns()
						> SHOOTER_WENCH_POT_FULL_OUT) {
			CommandBase::shooter->setWenchMotor(0.0);
			Logger::log(Logger::kWarning, "Watchdog",
					"Shooter motor over released!");
		}
		if (CommandBase::shooter->getWenchMotorSpeed() < 0
				&& CommandBase::shooter->getWLatch() == Shooter::kLatched) {
			CommandBase::shooter->setWenchMotor(0.0);
			Logger::log(Logger::kWarning, "Watchdog",
					"Shooter motor released without pawl disengaged!");
		}
		if (CommandBase::shooter->getWenchMotorSpeed()> 0) {
			if (CommandBase::shooter->getTurns() < 0) {
				CommandBase::shooter->setWenchMotor(0.0);
				Logger::log(Logger::kWarning, "Watchdog",
						"Shooter motor overdrawn sensed by potentiometer!");
			}
			if (CommandBase::shooter->getTurns()
					< SHOOTER_WENCH_POT_REVERSE_ALLOW) {
#if SHOOTER_LIMITSWITCH
				if (CommandBase::shooter->isLatchedByProximity()) {
					CommandBase::shooter->setWenchMotor(0.0);
					Logger::log(Logger::kWarning, "Watchdog",
							"Shooter motor overdrawn sensed by proximity switch!");
				}
#endif
				if (CommandBase::shooter->isLatchedByPattern()) {
					CommandBase::shooter->setWenchMotor(0.0);
					Logger::log(Logger::kWarning, "Watchdog",
							"Shooter motor overdrawn sensed by latch pattern!");
				}
			}
		}
		if (CommandBase::shooter->isShooterMotorStalled()
				&& CommandBase::shooter->getWenchMotorSpeed()>0
				&& CommandBase::shooter->getTurns() > 0.125 && CommandBase::shooter->getWLatch() != Shooter::kLatched) {
			Command *running = CommandBase::shooter->GetCurrentCommand();
			if (running != NULL) {
				if (running->GetName().compare("WLatch_Latched") != 0) {
					printf(
							"Watchdog: Killed command %s due to shooter stall!\n",
							running->GetName().c_str());
					Scheduler::GetInstance()->Remove(running);
					Scheduler::GetInstance()->AddCommand(new WLatch(Shooter::kLatched));
				}
			}
		}
	}
}

START_ROBOT_CLASS(MFCBot)
;

