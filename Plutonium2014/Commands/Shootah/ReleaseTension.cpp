#include "ReleaseTension.h"
#include "../../Subsystems/Shootah.h"
#include "../../Robotmap.h"

ReleaseTension::ReleaseTension(float setTurns) {
	Requires(shootah);
	this->setTurns = setTurns;
}

void ReleaseTension::Initialize() {
	isDone = true;
	if(!shootah->isReallyDrawnBack()){
		isDone = false;
	}
}

void ReleaseTension::Execute() {
	shootah->setWenchMotor(SHOOTAH_WENCH_MOTOR_FULL_FORWARD);
}

bool ReleaseTension::IsFinished() {
	return (shootah->getTurns() >= setTurns || !isDone);
}

void ReleaseTension::End() {
	shootah->setWenchMotor(0);
}

void ReleaseTension::Interrupted() {
	shootah->setWenchMotor(0);
}
