#include "HotGoalWait.h"

#include "../../Utils/Logger.h"

HotGoalWait::HotGoalWait() {
	SetTimeout(5.0);
	table = NetworkTable::GetTable("SmartDashboard");
}
void HotGoalWait::Initialize() {
	stability = 0;
}
void HotGoalWait::Execute() {
}
bool HotGoalWait::IsFinished() {
	if (table->GetBoolean("HotGoal", false)) {
		Logger::log(Logger::kInfo, "Automatic", "Hot Goal Terminated");
		return true;
	}
	return IsTimedOut() || DriverStation::GetInstance()->GetMatchTime() > 5.5;
}
void HotGoalWait::End() {
}

void HotGoalWait::Interrupted() {
}
