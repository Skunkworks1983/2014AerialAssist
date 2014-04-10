#include "HotGoalWait.h"

#include "../../Utils/Logger.h"

HotGoalWait::HotGoalWait() {
	SetTimeout(5.0);
}
void HotGoalWait::Initialize() {
	table = NetworkTable::GetTable("DSVision");
	table->PutBoolean("HotGoal", false);
	stability = 0;
}
void HotGoalWait::Execute() {
}
bool HotGoalWait::IsFinished() {
	if (table->GetBoolean("HotGoal", false)) {
		stability++;
	} else {
		stability = 0;
	}
	if (stability > 15) {
		Logger::log(Logger::kFine, "Automatic", "Hot Goal Terminated");
	}
	return IsTimedOut() || DriverStation::GetInstance()->GetMatchTime() > 5.0 || stability > 15;
}
void HotGoalWait::End() {
}

void HotGoalWait::Interrupted() {
}
