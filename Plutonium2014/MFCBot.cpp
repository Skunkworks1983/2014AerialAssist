#include "WPILib.h"
#include "Commands/Command.h"
#include "MFCBot.h"
#include "CommandBase.h"
#include "Utils/SolenoidPair.h"
#include "Robotmap.h"
#include "Utils/StallableMotor.h"
#include "Subsystems/Pterodactyl.h"

MFCBot::MFCBot() {
	lw = NULL;
//	new SolenoidPair(DRIVE_SHIFT_HIGH, DRIVE_SHIFT_LOW); // WORKS
//	new SolenoidPair(SHOOTAH_PNEUMATIC_W_LATCH);
//	new SolenoidPair(SHOOTAH_PNEUMATIC_S_LATCH);
//	new SolenoidPair(COLLECTOR_JAW_SOLENOID_A,
//		COLLECTOR_JAW_SOLENOID_B);
//	new AnalogChannel(1);
//	new AnalogChannel(2);
//	new Talon(SHOOTAH_MOTOR_WENCH);
//	new Relay(2,2);
//	new Talon(COLLECTOR_ROLLER_MOTOR_LEFT);
//	new Talon(COLLECTOR_ROLLER_MOTOR_RIGHT);
	dont = 0;
}

MFCBot::~MFCBot() {

}

void MFCBot::RobotInit() {
	CommandBase::init();
	lw = LiveWindow::GetInstance();
	CommandBase::oi->registerButtonListeners();
	SmartDashboard::PutData(Scheduler::GetInstance());
	SmartDashboard::PutNumber("Pterodactyl",CommandBase::pterodactyl->getAngle());
}

void MFCBot::AutonomousInit() {
}

void MFCBot::AutonomousPeriodic() {
	Scheduler::GetInstance()->Run();
	WatchDog();
}

void MFCBot::TeleopInit() {
}

void MFCBot::TeleopPeriodic() {
	Scheduler::GetInstance()->Run();
	WatchDog();
	StallableMotor::updateControllers();
	if (dont++ > 10) {
		dont=0;
	}
}

void MFCBot::TestPeriodic() {
	lw->Run();
	WatchDog();
}

void MFCBot::WatchDog() {
	if (CommandBase::shootah->getWenchMotorSpeed() > 0 && CommandBase::shootah->getTurns() > 8) {
		CommandBase::shootah->setWenchMotor(0.0);
	}
	
	if (CommandBase::shootah->getWenchMotorSpeed() < 0 && (CommandBase::shootah->getTurns() < 0 || CommandBase::shootah->getPullBackSwitch())) {
		CommandBase::shootah->setWenchMotor(0.0);
	}
}

START_ROBOT_CLASS(MFCBot)
;

