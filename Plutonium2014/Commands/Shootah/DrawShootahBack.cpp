#include "DrawShootahBack.h"
#include "../../Robotmap.h"

DrawShootahBack::DrawShootahBack() {
	Requires(shootah);
}

void DrawShootahBack::Initialize() {

}

void DrawShootahBack::Execute() {
	if(!shootah->isReallyDrawnBack()){
		shootah->setWenchMotor(SHOOTAH_WENCH_MOTOR_FULL_BACK);
	}
	
	printf("Turns: %f, PullBackSwitch: %d, Voltage: %f, isDrawnBack: %d\n",
		shootah->getTurns(), shootah->getPullBackSwitch(), shootah->getPotVoltage(), shootah->isReallyDrawnBack());
}

bool DrawShootahBack::IsFinished() {
	return shootah->isReallyDrawnBack();
}

void DrawShootahBack::End() {
	shootah->setWenchMotor(0);
}

void DrawShootahBack::Interrupted() {
	shootah->setWenchMotor(0);
}
