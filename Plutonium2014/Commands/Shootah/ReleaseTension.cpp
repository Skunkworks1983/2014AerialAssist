#include "ReleaseTension.h"
#include "../../Subsystems/Shootah.h"
#include "../../Robotmap.h"
#include <math.h>

ReleaseTension::ReleaseTension(float setTurns) :
	CommandBase(CommandBase::createNameFromFloat("ReleaseTension", setTurns)) {
	Requires(shootah);
	this->setTurns = setTurns;
}

void ReleaseTension::Initialize() {
	isDone = true;
	if (!shootah->isReallyDrawnBack()) {
		printf("Run release without draw.\n");
		isDone = false;
	}
}

void ReleaseTension::Execute() {
	if (shootah->getTurns() >= setTurns) {
		shootah->setWenchMotor(SHOOTAH_WENCH_MOTOR_FULL_RELEASE);
	} else {
		shootah->setWenchMotor(-SHOOTAH_WENCH_MOTOR_FULL_RELEASE);
	}
}

bool ReleaseTension::IsFinished() {
	return (fabs(shootah->getTurns() - setTurns)
			< SHOOTAH_WENCH_PAYOUT_TOLERANCE) || !isDone;
}

void ReleaseTension::End() {
	shootah->setWenchMotor(0);
}

void ReleaseTension::Interrupted() {
	shootah->setWenchMotor(0);
}
