#include "PrepareZeDevice.h"
#include "../../Subsystems/Shootah.h"
#include "../../Robotmap.h"

PrepareZeDevice::PrepareZeDevice(float setpoint) {
	Requires(shootah);
	this->setpoint = setpoint;
}

void PrepareZeDevice::Initialize() {
	if (shootah->pullbackDone()) {
		if (!shootah->getLatch()) {
			shootah->setLatch(true);
		}
		
		if (shootah->getBrake()) {
			shootah->setBrake(false);
		}
		
		shootah->setWenchMotor(SHOOTAH_PREPARE_SPEED);
	}
}

void PrepareZeDevice::Execute() {
	// Don't need this even, I'm probably doing it wrong...
}

bool PrepareZeDevice::IsFinished() {
	if (!shootah->isDistance(setpoint)) {
		return false;
	}
	return true;
}

void PrepareZeDevice::End() {
	shootah->setBrake(true);
	shootah->setWenchMotor(0);
}

void PrepareZeDevice::Interrupted() {
	shootah->setBrake(true);
	shootah->setWenchMotor(0);
}
