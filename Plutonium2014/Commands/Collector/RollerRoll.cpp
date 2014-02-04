#include "RollerRoll.h"

RollerRoll::RollerRoll(float speed) {
	Requires(collector);
	this->speed = speed;
}

void RollerRoll::Initialize() {
	collector->setRollerSpeed(speed);
}

int magic = 0;
void RollerRoll::Execute() {
	/*if(collector->getcollector->getDiff()f() < 0 - THRESH){
		collector->setRollerPIDSpeed(speed + collector->getDiff());
	} else if(collector->getDiff() > 0 + THRESH){
		collector->setRollerPIDSpeed(speed + collector->getDiff());
	}*/
	 
	//collector->setRollerSpeed(speed + collector->getDiff());
	//collector->setRollerSpeed(speed);
	if (magic++ > 10){
		magic = 0;
		printf("DesiredSpeed: %f\tSpeed: %f\tDistance: %f\n", speed,
				collector->getRollerSpeed(), collector->getRollerDistance());
		SmartDashboard::PutNumber("RollerSpeed", collector->getRollerSpeed());
	}
}

bool RollerRoll::IsFinished() {
	if (collector->isBallDetected()) {
		return true;
	}
	return false;
}

void RollerRoll::End() {
	collector->setRollerSpeed(0.0);
}

void RollerRoll::Interrupted() {
	collector->setRollerSpeed(0.0);
}
