#include "HotGoalWait.h"

#include "../../Utils/Logger.h"

HotGoalWait::HotGoalWait() {
	SetTimeout(5.0);
}
void HotGoalWait::Initialize() {
	stability = 0;
	table = NetworkTable::GetTable("SmartDashboard");
}
void HotGoalWait::Execute() {
}
bool HotGoalWait::IsFinished() {
	if (table->GetBoolean("HotGoal", false)) {//beaglebone->isGyroActive() && beaglebone->gyro.roll == 1.0f) {
		stability++;
	} else {
		stability = 0;
	}
	if (stability > 1) {
		Logger::log(Logger::kFine, "Automatic", "Hot Goal Terminated");
	}
	return IsTimedOut() || DriverStation::GetInstance()->GetMatchTime() > 5.5 || stability > 1;
}
void HotGoalWait::End() {
}

void HotGoalWait::Interrupted() {
}
