#include "RollerRoll.h"

RollerRoll::RollerRoll(float speed) {
	Requires(collector);
	this->speed = speed;
}

void RollerRoll::Initialize() {
}

int magic = 0;
void RollerRoll::Execute() {
	/*
	 if(dif < 0 - THRESH){
	 collector->setRollerPIDSpeed(speed + dif);
	 }else if(dif > 0 + THRESH){
	 collector->setRollerPIDSpeed(speed + dif);
	 }
	 */
	//collector->setRollerSpeed(speed + dif);
	collector->setRollerSpeed(speed);
	/*if (magic++ > 10){
		magic = 0;
		printf("DesiredSpeed: %f\tSpeed: %f\tDistance: %f\n", speed,
				collector->getRollerSpeed(), collector->getRollerDistance());
		SmartDashboard::PutNumber("RollerSpeed", collector->getRollerSpeed());
	}*/
}

bool RollerRoll::IsFinished() {
	return false;
}

void RollerRoll::End() {
	collector->setRollerSpeed(0.0);
}

void RollerRoll::Interrupted() {
	collector->setRollerSpeed(0.0);
}
