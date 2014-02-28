#include "WPILib.h"
#include "Commands/Command.h"
#include "MFCBot.h"
#include "CommandBase.h"
#include "Utils/Actuators/SolenoidPair.h"
#include "Robotmap.h"
#include "Utils/Actuators/StallableMotor.h"
#include "Subsystems/Pterodactyl.h"
#include "Commands/Shooter/Latches/WLatch.h"
#include "Commands/Autonomous/Autonomous.h"
#include "Subsystems/Pterodactyl.h"

MFCBot::MFCBot() {
	lw = NULL;
	dont = 0;
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
}

void MFCBot::AutonomousInit() {
	Scheduler::GetInstance()->RemoveAll();
	((Command*) chooser->GetSelected())->Start();
}

void MFCBot::AutonomousPeriodic() {
	Scheduler::GetInstance()->Run();
	WatchDog();
	if (dont++ > 10) {
		printf	("Encoder Left: %f, Encoder Right: %f \n", CommandBase::driveBase->getLeftEncoder(), CommandBase::driveBase->getRightEncoder());
		dont = 0;
	}
}

void MFCBot::TeleopInit() {
	Scheduler::GetInstance()->RemoveAll();
}

void MFCBot::TeleopPeriodic() {
	SmartDashboard::PutData(Scheduler::GetInstance());
	Scheduler::GetInstance()->Run();
	WatchDog();
	StallableMotor::updateControllers();
	if (dont++ > 10) {
		SmartDashboard::PutNumber("Winch rate", CommandBase::shooter->getTurnRate());
		SmartDashboard::PutNumber("Winch position", CommandBase::shooter->getTurns());
		CommandBase::collector->getRollerSpeed();
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
		if (CommandBase::shooter->getWenchMotorSpeed() < 0
				&& CommandBase::shooter->getTurns()
						> SHOOTER_WENCH_POT_FULL_OUT) {
			CommandBase::shooter->setWenchMotor(0.0);
			printf("Watchdog: Shooter motor overeleased!\n");
		}
		if (CommandBase::shooter->getWenchMotorSpeed() > 0) {
			if (CommandBase::shooter->getTurns() < 0) {
				CommandBase::shooter->setWenchMotor(0.0);
				printf("Watchdog: Shooter motor overdrawn: POT FILTER!\n");
			}
#if SHOOTER_LIMITSWITCH
			if (CommandBase::shooter->isLatchedByProximity()) {
				CommandBase::shooter->setWenchMotor(0.0);
				printf("Watchdog: Shooter motor overdrawn: PULLBACK FILTER!\n");
			}
#endif
			if (CommandBase::shooter->isLatchedByPattern()) {
				CommandBase::shooter->setWenchMotor(0.0);
				printf(
						"Watchdog: Shooter motor overdrawn: SHOOTER LATCH FILTER!\n");
			}
		}
	}
}

START_ROBOT_CLASS( MFCBot);

