#include "ReleaseTension.h"
#include "../../../Subsystems/Shooter.h"
#include "../../../Robotmap.h"
#include <math.h>
int ReleaseTension::runCount = 0;

ReleaseTension::ReleaseTension(float setTurns) :
	CommandBase(CommandBase::createNameFromFloat("ReleaseTension", setTurns)) {
	Requires(shooter);
	this->setTurns = setTurns;
	this->isDone = false;
}

void ReleaseTension::Initialize() {
	CommandBase::shooter->lastReleasePosition = setTurns;
	isDone = true;
	if (!shooter->isReallyDrawnBack()) {
		printf("Warning: Run release without draw.\n");
		//isDone = false;
	}
}

void ReleaseTension::Execute() {
	if (shooter->getTurns() <= setTurns) {
		shooter->setWenchMotor(SHOOTER_WENCH_MOTOR_FULL_RELEASE);
	} else {
		shooter->setWenchMotor(-SHOOTER_WENCH_MOTOR_FULL_RELEASE);
	}
	SmartDashboard::PutNumber("Current Winch", shooter->getTurns());
	SmartDashboard::PutNumber("Current Winch Target", setTurns);
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
