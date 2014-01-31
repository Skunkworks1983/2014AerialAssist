#include "DrawZeDevice.h"
#include "../../Robotmap.h"

DrawZeDevice::DrawZeDevice() {
	Requires(shootah);
}

void DrawZeDevice::Initialize() {
	if (shootah->getLatch()) {
		shootah->setLatch(false);
	}
	
	shootah->setWenchMotor(SHOOTAH_DRAW_POSITION_FULL);
}

void DrawZeDevice::Execute() {
	/*if (!shootah->isWinchPIDSetpoint() && shootah->pullbackDone()) {
		// Would be something that keeps the setpoint in check if we check that in the isFinished
	}*/
}

bool DrawZeDevice::IsFinished() { // Just starting this, umm, yeah
	/*if (!shootah->pullbackDone()) {
		return false;
	}*/
	
	return true;
}

void DrawZeDevice::End() {
	/*shootah->setWenchPIDState(false);*/
	shootah->setWenchMotor(0);
	shootah->setLatch(true);
}

void DrawZeDevice::Interrupted() {
	//shootah->setWenchPIDState(false);
	//shootah->setWinchPID(0);
	shootah->setWenchMotor(0);
	shootah->setLatch(true);
}
