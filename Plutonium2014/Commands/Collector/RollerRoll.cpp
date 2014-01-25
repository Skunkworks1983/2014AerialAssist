#include "RollerRoll.h"

RollerRoll::RollerRoll(float speed) {
	Requires(collector);
	this->speed = speed;
}

void RollerRoll::Initialize() {
	
}

void RollerRoll::Execute() {
	collector->setRollerPIDSpeed(speed);
	printf("%f\n", speed);
}

bool RollerRoll::IsFinished() {
	return false;
}

void RollerRoll::End() {
	collector->setRollerPIDSpeed(0);
}

void RollerRoll::Interrupted() {
	collector->setRollerPIDSpeed(0);
}
