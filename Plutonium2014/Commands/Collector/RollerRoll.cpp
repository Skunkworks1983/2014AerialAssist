#include "RollerRoll.h"

RollerRoll::RollerRoll(float speed) :
	CommandBase(CommandBase::createNameFromFloat("RollerRoll", speed)) {
	Requires(collector);
	this->speed = speed;
}

void RollerRoll::Initialize() {
	collector->setRollerSpeed(speed);
	//collector->PIDWrite(0.9);
}

void RollerRoll::Execute() {
	//printf("DesiredSpeed: %f\tSpeed: %f\tDistance: %f\tisBallDetected: %d \n ", speed,
	//		collector->getRollerSpeed(), collector->getRollerDistance(), collector->isBallDetected());
	SmartDashboard::PutNumber("RollerSpeed", collector->getRollerSpeed());
}

bool RollerRoll::IsFinished() {
	return collector->isBallDetected();
}

void RollerRoll::End() {
	collector->setRollerSpeed(0.0);
	//collector->PIDWrite(0);
}

void RollerRoll::Interrupted() {
	collector->setRollerSpeed(0.0);
	//collector->PIDWrite(0);
}
