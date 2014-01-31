#include "PrepareZeDevice.h"
#include "../../Subsystems/Shootah.h"

PrepareZeDevice::PrepareZeDevice(float setpoint) {
	Requires(shootah);
	this->setpoint = setpoint;
}

void PrepareZeDevice::Initialize() {
	/*if (shootah->pullbackDone()) {
		if (shootah->getLatch()) {
			shootah->setLatch(false);
		}
		
		shootah->setWenchMotor(setpoint);
	}*/
}

void PrepareZeDevice::Execute() {
	// Don't need this even, I'm probably doing it wrong...
}

bool PrepareZeDevice::IsFinished() {
	/*if (!shootah->isWenchPIDSetpoint()) {
		return false;
	}*/
	return true;
}

void PrepareZeDevice::End() {
	//shootah->setWenchPIDState(false);
	shootah->setLatch(true); //nothing would have set it so we can assume it's off
}

void PrepareZeDevice::Interrupted() {
	shootah->setLatch(true);
}
