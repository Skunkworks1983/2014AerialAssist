#include "PrepareZeDevice.h"
#include "../../Subsystems/Shootah.h"

PrepareZeDevice::PrepareZeDevice(float setpoint) {
	Requires(shootah);
	this->setpoint = setpoint;
}

// Called just before this Command runs the first time
void PrepareZeDevice::Initialize() {
	if (shootah->getShootahPosition() == Shootah::kBack) {
		shootah->setCoffeeTable(false);
		shootah->setWinchPID(setpoint);
	}
}

// Called repeatedly when this Command is scheduled to run
void PrepareZeDevice::Execute() {
	// Don't need this even, I'm probably doing it wrong...
}

// Make this return true when this Command no longer needs to run execute()
bool PrepareZeDevice::IsFinished() {
	if (!shootah->isWinchPIDSetpoint() && (shootah->getShootahPosition() == Shootah::kBack || shootah->getShootahPosition() == Shootah::kAdjusting)) {
		return false;
	}
	return true;
}

// Called once after isFinished returns true
void PrepareZeDevice::End() {
	shootah->setWinchPIDState(false);	
	shootah->setCoffeeTable(true); //nothing would have set it so we can assume it's off
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void PrepareZeDevice::Interrupted() {
	shootah->setWinchPIDState(false);
	shootah->setCoffeeTable(true);
}
