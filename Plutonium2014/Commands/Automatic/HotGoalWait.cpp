#include "HotGoalWait.h"

#include "../../Utils/Logger.h"

HotGoalWait::HotGoalWait() {
	SetTimeout(5.0);
}
void HotGoalWait::Initialize() {
	stability = 0;
}
void HotGoalWait::Execute() {
}
bool HotGoalWait::IsFinished() {
	if (beaglebone->isGyroActive() && beaglebone->gyro.roll == 1.0f) {
		stability++;
	} else {
		stability = 0;
	}
	if (stability > 15) {
		Logger::log(Logger::kFine, "Automatic", "Hot Goal Terminated");
	}
	return IsTimedOut() || DriverStation::GetInstance()->GetMatchTime() > 7.0 || stability > 15;
}
void HotGoalWait::End() {
}

void HotGoalWait::Interrupted() {
}
