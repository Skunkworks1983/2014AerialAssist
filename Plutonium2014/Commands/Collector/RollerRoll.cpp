#include "RollerRoll.h"

RollerRoll::RollerRoll(float speed) {
	Requires(collector);
}

void RollerRoll::Initialize() {
	
}

void RollerRoll::Execute() {
	collector->setRollerSpeed(speed);
}

bool RollerRoll::IsFinished() {
	return false;
}

void RollerRoll::End() {
	collector->setRollerSpeed(0);
}

void RollerRoll::Interrupted() {
	collector->setRollerSpeed(0);
}
