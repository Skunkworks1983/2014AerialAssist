#include "ReleaseTension.h"
#include "../../Subsystems/Shootah.h"
#include "../../Robotmap.h"

ReleaseTension::ReleaseTension(float setTurns) {
	Requires(shootah);
	this->setTurns = setTurns;
}

void ReleaseTension::Initialize() {
}

void ReleaseTension::Execute() {
	shootah->setWenchMotor(SHOOTAH_WENCH_MOTOR_FULL_FORWARD);
	printf("Turns: %f, PullBackSwitch: %d, Buttons: %d, Voltage: %f, isDrawnBack: %d, isDone: %d \n",
			shootah->getTurns(), shootah->getPullBackSwitch(), shootah->getInductiveSwitch(), shootah->getPotVoltage(), shootah->isReallyDrawnBack(), isDone);
}

bool ReleaseTension::IsFinished() {
	return (shootah->getTurns() >= setTurns);
}

void ReleaseTension::End() {
	//shootah->setBrake(true);
	shootah->setWenchMotor(0);
}

void ReleaseTension::Interrupted() {
	//shootah->setBrake(true);
	shootah->setWenchMotor(0);
}
