#include "DrawZeDevice.h"
#include "../../Robotmap.h"

DrawZeDevice::DrawZeDevice() {
	Requires(shootah);
}

void DrawZeDevice::Initialize() {
	shootah->setLatch(true);
}

void DrawZeDevice::Execute() {
	if(!shootah->isReallyDrawnBack()){
		shootah->setWenchMotor(SHOOTAH_WENCH_FULL_BACK);
	} else{
		shootah->setWenchMotor(0);
	}
}

bool DrawZeDevice::IsFinished() {
	return shootah->isReallyDrawnBack();
}

void DrawZeDevice::End() {
	shootah->setWenchMotor(0);
}

void DrawZeDevice::Interrupted() {
	shootah->setWenchMotor(0);
	shootah->setLatch(true);
}
