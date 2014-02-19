#include "FullTension.h"
#include "../../../Robotmap.h"

FullTension::FullTension() {
	Requires(shooter);
}

void FullTension::Initialize() {

}

void FullTension::Execute() {
	if (!shooter->isReallyDrawnBack()) {
		if (shooter->getTurns() < SHOOTER_WENCH_SETPOINT_THRESH) {
			shooter->setWenchMotor(SHOOTER_WENCH_MOTOR_FULL_BACK_NEAR);
		} else {
			shooter->setWenchMotor(SHOOTER_WENCH_MOTOR_FULL_BACK);
		}
	}
}

bool FullTension::IsFinished() {
	return shooter->isReallyDrawnBack();
}

void FullTension::End() {
	shooter->setWenchMotor(0);
}

void FullTension::Interrupted() {
	shooter->setWenchMotor(0);
}
