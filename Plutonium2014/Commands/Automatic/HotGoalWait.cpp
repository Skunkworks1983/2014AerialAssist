#include "HotGoalWait.h"

HotGoalWait::HotGoalWait() {
	SetTimeout(5.0);
}
void HotGoalWait::Initialize() {
	table = NetworkTable::GetTable("DSVision");
	table->PutBoolean("HotGoal", false);
}
void HotGoalWait::Execute() {
}
bool HotGoalWait::IsFinished() {
	return IsTimedOut() || DriverStation::GetInstance()->GetMatchTime() > 5.0 || table->GetBoolean("HotGoal", false);
}
void HotGoalWait::End() {
}

void HotGoalWait::Interrupted() {
}
