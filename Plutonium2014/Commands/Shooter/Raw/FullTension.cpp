#include "FullTension.h"
#include "../../../Robotmap.h"
#include "../../../Utils/Time.h"
#include <stdio.h>

FullTension::FullTension() {
	Requires(shooter);
	SetInterruptible(false);
}

void FullTension::Initialize() {
}

void FullTension::Execute() {
	if (!shooter->isReallyDrawnBack()) {
		if (shooter->getTurns() < SHOOTER_WENCH_POT_BACK_NEAR) {
			shooter->setWenchMotor(SHOOTER_WENCH_MOTOR_FULL_BACK_NEAR);
		} else {
			shooter->setWenchMotor(SHOOTER_WENCH_MOTOR_FULL_BACK);
		}
	}
}

bool FullTension::IsFinished() {
	bool state = shooter->isReallyDrawnBack();
	if (shooter->isLatchedByPattern()) {
		printf("Pattern stop\n");
	}
#if SHOOTER_LIMITSWITCH
	if (shooter->isLatchedByProximity()) {
		printf("Proximity stop\n");
	}
#endif
	if (shooter->getTurns() <= SHOOTER_WENCH_POT_BACK){
		printf("Pot stop\n");
	}
	return state;
}

void FullTension::End() {
	printf("Ended Full Tension!\n");
	shooter->setWenchMotor(0);
}

void FullTension::Interrupted() {
	printf("Interrupted Full Tension!\n");
	shooter->setWenchMotor(0);
}
