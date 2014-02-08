#include "RollerRoll.h"

RollerRoll::RollerRoll(float speed) {
	Requires(collector);
	this->speed = speed;
}

void RollerRoll::Initialize() {
	collector->setRollerSpeed(speed);
}

int veryMagic = 5;
void RollerRoll::Execute() {
	/*if(collector->getcollector->getDiff()f() < 0 - THRESH){
	 collector->setRollerPIDSpeed(speed + collector->getDiff());
	 } else if(collector->getDiff() > 0 + THRESH){
	 collector->setRollerPIDSpeed(speed + collector->getDiff());
	 }*/
	//oldthresholdstuffs
	//collector->setRollerSpeed(speed + collector->getDiff());
	if (veryMagic++ == 5) {
		veryMagic = 0;
		printf("DesiredSpeed: %f\tSpeed: %f\tDistance: %f\tisBallDetected: %d \n ", speed,
				collector->getRollerSpeed(), collector->getRollerDistance(), collector->isBallDetected());
	}
	SmartDashboard::PutNumber("RollerSpeed", collector->getRollerSpeed());
}

bool RollerRoll::IsFinished() {
	return collector->isBallDetected();
}

void RollerRoll::End() {
	collector->setRollerSpeed(0.0);
}

void RollerRoll::Interrupted() {
	collector->setRollerSpeed(0.0);
}
