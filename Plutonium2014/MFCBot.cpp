#include "WPILib.h"
#include "Commands/Command.h"
#include "MFCBot.h"
#include "CommandBase.h"

void MFCBot::RobotInit() {
	CommandBase::init();
	lw = LiveWindow::GetInstance();
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

START_ROBOT_CLASS(MFCBot);

