#include "DrawShootahBack.h"
#include "../../Robotmap.h"

DrawShootahBack::DrawShootahBack() {
	Requires(shootah);
}

void DrawShootahBack::Initialize() {

}

void DrawShootahBack::Execute() {
	if (!shootah->isReallyDrawnBack()) {
		if (shootah->getTurns() < SHOOTAH_WENCH_SETPOINT_THRESH) {
			shootah->setWenchMotor(SHOOTAH_WENCH_MOTOR_FULL_BACK_NEAR);
		} else {
			shootah->setWenchMotor(SHOOTAH_WENCH_MOTOR_FULL_BACK);
		}
	}
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
