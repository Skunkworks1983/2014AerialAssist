#include "PrepareZeDevice.h"
#include "../../Subsystems/Shootah.h"

PrepareZeDevice::PrepareZeDevice(float setpoint) {
	Requires(shootah);
	this->setpoint = setpoint;
}

void PrepareZeDevice::Initialize() {
	if (shootah->getShootahPosition() == Shootah::kBack) {
		shootah->setCoffeeTable(false);
		shootah->setWinchPID(setpoint);
	}
}

void PrepareZeDevice::Execute() {
	// Don't need this even, I'm probably doing it wrong...
}

bool PrepareZeDevice::IsFinished() {
	if (!shootah->isWinchPIDSetpoint() && (shootah->getShootahPosition() == Shootah::kBack || shootah->getShootahPosition() == Shootah::kAdjusting)) {
		return false;
	}
	return true;
}

void PrepareZeDevice::End() {
	shootah->setWinchPIDState(false);	
	shootah->setWinchPID(0);
	shootah->setCoffeeTable(true); //nothing would have set it so we can assume it's off
}

void PrepareZeDevice::Interrupted() {
	shootah->setWinchPIDState(false);
	shootah->setCoffeeTable(true);
}
