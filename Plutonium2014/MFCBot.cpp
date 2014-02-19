#include "WPILib.h"
#include "Commands/Command.h"
#include "MFCBot.h"
#include "CommandBase.h"
#include "Utils/Actuators/SolenoidPair.h"
#include "Robotmap.h"
#include "Utils/Actuators/StallableMotor.h"
#include "Subsystems/Pterodactyl.h"
#include "Commands/Shooter/Latches/WLatch.h"

MFCBot::MFCBot() {
	lw = NULL;
	dont = 0;
}

MFCBot::~MFCBot() {

}

void MFCBot::RobotInit() {
	CommandBase::init();
	lw = LiveWindow::GetInstance();
	CommandBase::oi->registerButtonListeners();
}

void MFCBot::AutonomousInit() {
	Scheduler::GetInstance()->RemoveAll();
}

void MFCBot::AutonomousPeriodic() {
	Scheduler::GetInstance()->Run();
	WatchDog();
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
		dont=0; //This kills the bug
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
		dont=0;
	}
	WatchDog();
}

void MFCBot::WatchDog() {
	if (CommandBase::shooter!=NULL) {
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
			if (CommandBase::shooter->getPullBackSwitch()) {
				CommandBase::shooter->setWenchMotor(0.0);
				printf("Watchdog: Shooter motor overdrawn: PULLBACK FILTER!\n");
			}
#endif
			if (CommandBase::shooter->isLatchedByPattern()) {
				CommandBase::shooter->setWenchMotor(0.0);
				printf("Watchdog: Shooter motor overdrawn: SHOOTER LATCH FILTER!\n");
			}
		}
	}
}

START_ROBOT_CLASS(MFCBot)
;

