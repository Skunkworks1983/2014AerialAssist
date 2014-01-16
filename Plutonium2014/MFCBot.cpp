#include "WPILib.h"
#include "Commands/Command.h"
#include "MFCBot.h"
#include "CommandBase.h"

MFCBot::MFCBot() {
	lw = NULL;
}

MFCBot::~MFCBot() {

}

void MFCBot::RobotInit() {
	CommandBase::init();
	lw = LiveWindow::GetInstance();
	CommandBase::oi->registerButtonListeners();
}

void MFCBot::AutonomousInit() {
}

void MFCBot::AutonomousPeriodic() {
	Scheduler::GetInstance()->Run();
}

void MFCBot::TeleopInit() {

}

void MFCBot::TeleopPeriodic() {
	Scheduler::GetInstance()->Run();
}

void MFCBot::TestPeriodic() {
	lw->Run();
}

START_ROBOT_CLASS(MFCBot)
;

