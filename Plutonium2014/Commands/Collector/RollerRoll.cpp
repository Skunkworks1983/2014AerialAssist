#include "RollerRoll.h"

RollerRoll::RollerRoll(float speed) {
	Requires(collector);
	this->speed = speed;
}

void RollerRoll::Initialize() {
	collector->setRollerSpeedLeft(speed);
	collector->setRollerSpeedRight(-speed);
}

void RollerRoll::Execute() {
	//printf("DesiredSpeed: %f\tSpeed: %f\tDistance: %f\tisBallDetected: %d \n ", speed,
	//		collector->getRollerSpeed(), collector->getRollerDistance(), collector->isBallDetected());
	//SmartDashboard::PutNumber("RollerSpeed", collector->getRollerSpeed());
}

bool RollerRoll::IsFinished() {
	return collector->isBallDetected();
}

void RollerRoll::End() {
	collector->setRollerSpeedLeft(0.0);
	collector->setRollerSpeedRight(0.0);
}

void RollerRoll::Interrupted() {
	collector->setRollerSpeedLeft(0.0);
	collector->setRollerSpeedRight(0.0);
}
