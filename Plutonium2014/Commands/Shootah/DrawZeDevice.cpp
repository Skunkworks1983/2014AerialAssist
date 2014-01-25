#include "DrawZeDevice.h"
#include "../../Robotmap.h"

DrawZeDevice::DrawZeDevice() {
	Requires(shootah);
}

void DrawZeDevice::Initialize() {
	if (shootah->getCoffeeTable()) {
		shootah->setCoffeeTable(false);
	}
	
	shootah->setWinchPID(SHOOTAH_DRAW_POSITION_FULL);
}

void DrawZeDevice::Execute() {
	/*if (!shootah->isWinchPIDSetpoint() && shootah->pullbackDone()) {
		// Would be something that keeps the setpoint in check if we check that in the isFinished
	}*/
}

bool DrawZeDevice::IsFinished() { // Just starting this, umm, yeah
	if (!shootah->pullbackDone()) { 
		return false;
	}
	
	return true;
}

void DrawZeDevice::End() {
	shootah->setWinchPIDState(false);
	shootah->setWinchPID(0);
	shootah->setCoffeeTable(true);
}

void DrawZeDevice::Interrupted() {
	shootah->setWinchPIDState(false);
	//shootah->setWinchPID(0);
	shootah->setCoffeeTable(true);
}
