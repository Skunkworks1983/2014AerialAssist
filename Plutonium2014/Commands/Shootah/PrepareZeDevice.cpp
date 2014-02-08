#include "PrepareZeDevice.h"
#include "../../Subsystems/Shootah.h"
#include "../../Robotmap.h"

PrepareZeDevice::PrepareZeDevice(float setTurns) {
	Requires(shootah);
	this->setTurns = setTurns;
	isDone = false;
}

void PrepareZeDevice::Initialize() {
	if (shootah->isReallyDrawnBack()) {
		/*if (!shootah->getLatch()) {
			shootah->setLatch(true);
		}
		if (shootah->getBrake()) {
			shootah->setBrake(false);
		}
		shootah->setWenchMotor(SHOOTAH_PREPARE_SPEED);*/
		isDone = false;
	}
	else{
		isDone = true;
	}
}

void PrepareZeDevice::Execute() {
	shootah->setWenchMotor(SHOOTAH_WENCH_MOTOR_FULL_FORWARD);
	printf("Turns: %f, PullBackSwitch: %d, Buttons: %d, Voltage: %f, isDrawnBack: %d, isDone: %d \n",
			shootah->getTurns(), shootah->getPullBackSwitch(), shootah->getInductiveSwitch(), shootah->getPotVoltage(), shootah->isReallyDrawnBack(), isDone);
}

bool PrepareZeDevice::IsFinished() {
	return (shootah->getTurns() >= setTurns) || isDone;
}

void PrepareZeDevice::End() {
	//shootah->setBrake(true);
	shootah->setWenchMotor(0);
}

void PrepareZeDevice::Interrupted() {
	//shootah->setBrake(true);
	shootah->setWenchMotor(0);
}
