#include "ReleaseTension.h"
#include "../../../Subsystems/Shooter.h"
#include "../../../Robotmap.h"
#include <math.h>

ReleaseTension::ReleaseTension(float setTurns) :
	CommandBase(CommandBase::createNameFromFloat("ReleaseTension", setTurns)) {
	Requires(shooter);
	this->setTurns = setTurns;
	this->isDone = false;
}

void ReleaseTension::Initialize() {
	isDone = true;
	if (!shooter->isReallyDrawnBack()) {
		printf("Run release without draw.\n");
		isDone = false;
	}
}

void ReleaseTension::Execute() {
	if (shooter->getTurns() >= setTurns) {
		shooter->setWenchMotor(SHOOTER_WENCH_MOTOR_FULL_RELEASE);
	} else {
		shooter->setWenchMotor(-SHOOTER_WENCH_MOTOR_FULL_RELEASE);
	}
}

bool ReleaseTension::IsFinished() {
	return (fabs(shooter->getTurns() - setTurns)
			< SHOOTER_WENCH_PAYOUT_TOLERANCE) || !isDone;
}

void ReleaseTension::End() {
	shooter->setWenchMotor(0);
}

void ReleaseTension::Interrupted() {
	shooter->setWenchMotor(0);
}
