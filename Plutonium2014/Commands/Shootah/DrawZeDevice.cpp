#include "DrawZeDevice.h"
#include "../../Robotmap.h"

DrawZeDevice::DrawZeDevice() {
	Requires(shootah);
}

void DrawZeDevice::Initialize() {
	/*shootah->setLatch(true);
	if(shootah->getBrake()){
		shootah->setBrake(false);
	}*/
}

void DrawZeDevice::Execute() {
	if(!shootah->isReallyDrawnBack()){
		shootah->setWenchMotor(SHOOTAH_WENCH_MOTOR_FULL_BACK);
	}
	
	printf("Turns: %f, PullBackSwitch: %d, Buttons: %d, Voltage: %f, isDrawnBack: %d\n",
		shootah->getTurns(), shootah->getPullBackSwitch(), shootah->getInductiveSwitch(), shootah->getPotVoltage(), shootah->isReallyDrawnBack());
}

bool DrawZeDevice::IsFinished() {
	return shootah->isReallyDrawnBack();
}

void DrawZeDevice::End() {
	shootah->setWenchMotor(0);
}

void DrawZeDevice::Interrupted() {
	shootah->setWenchMotor(0);
	//shootah->setBrake(true);
}
