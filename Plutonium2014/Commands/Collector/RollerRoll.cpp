#include "RollerRoll.h"
#include "../../Utils/Time.h"

RollerRoll::RollerRoll(float speed) :
	CommandBase(CommandBase::createNameFromFloat("RollerRoll", speed)) {
	Requires(collector);
	this->speed = speed;
	this->timeWait = 0;
}

void RollerRoll::Initialize() {
	collector->setRollerSpeed(speed);
}

void RollerRoll::Execute() {
	if (!collector->isBallDetected() && speed <= 0 && timeWait == 0) {
		timeWait = getCurrentMillis();
	}
	SmartDashboard::PutNumber("RollerSpeed", collector->getRollerSpeed());
}

bool RollerRoll::IsFinished() {
	return (collector->isBallDetected() && speed >= 0)
			|| ((!collector->isBallDetected() && speed <= 0)
					&& (getCurrentMillis()- timeWait >= 1000));
}

void RollerRoll::End() {
	collector->setRollerSpeed(0.0);
	collector->setJawState(collector->isBallDetected() ? Collector::kClosed
			: Collector::kOpen);
}

void RollerRoll::Interrupted() {
	collector->setRollerSpeed(0.0);
	collector->setJawState(collector->isBallDetected() ? Collector::kClosed
			: Collector::kOpen);
}
