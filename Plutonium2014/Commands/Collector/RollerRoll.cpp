#include "RollerRoll.h"
// Utils
#include "../../Utils/Time.h"

RollerRoll::RollerRoll(float speed) :
	CommandBase(CommandBase::createNameFromFloat("RollerRoll", speed)) {
	Requires(collector);
	this->speed = speed;
	this->timeWait = 0;
}

void RollerRoll::Initialize() {
	collector->setRollerSpeed(speed);
	this->timeWait = 0;
	this->hasBall = collector->isBallDetected();
}

void RollerRoll::Execute() {
	this->hasBall = collector->isBallDetected();
	if (!hasBall && speed <= 0 && timeWait == 0) {
		timeWait = getCurrentMillis();
	}
	if (hasBall && speed > 0 && timeWait == 0) {
		timeWait = getCurrentMillis();
	}
}

bool RollerRoll::IsFinished() {
	this->hasBall = collector->isBallDetected();
	if (hasBall && speed >= 0) {
		return timeWait > 0 && getCurrentMillis() - timeWait >= 250;
	} else if (!hasBall && speed <=0) {
		return timeWait > 0 && getCurrentMillis() - timeWait >= 1500;
	}
	if (timeWait > 0 && getCurrentMillis() - timeWait >= 300 && !hasBall
			&& speed>0) {
		timeWait=0;
	}
	return false;
}

void RollerRoll::End() {
	collector->setRollerSpeed(0.0);
	collector->setJawState(speed < 0 ? Collector::kOpen : Collector::kClosed);
	// Don't need collector->setJawState(hasBall ? Collector::kClosed : Collector::kOpen);
}

void RollerRoll::Interrupted() {
	collector->setRollerSpeed(0.0);
}
