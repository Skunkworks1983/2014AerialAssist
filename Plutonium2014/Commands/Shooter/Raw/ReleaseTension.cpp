#include "ReleaseTension.h"
// CSTDLIB
#include <math.h>

// Utils
#include "../../../Utils/Logger.h"

// Backend
#include "../../../Subsystems/Shooter.h"
#include "../../../Robotmap.h"

ReleaseTension::ReleaseTension(float setTurns) :
	CommandBase(CommandBase::createNameFromFloat("ReleaseTension", setTurns)) {
	Requires(shooter);
	this->setTurns = setTurns;
	this->isDone = false;
}

void ReleaseTension::Initialize() {
	isDone = true;
	if (!shooter->isReallyDrawnBack()) {
		Logger::log(Logger::kWarning, "Shooter-ReleaseTension",
				"Running release without draw!");
		//isDone = false;
	}
}

void ReleaseTension::Execute() {
	float speed= SHOOTER_WENCH_MOTOR_FULL_RELEASE;
	if (fabs(shooter->getTurns() - setTurns)
			< SHOOTER_WENCH_PAYOUT_TOLERANCE_NEAR) {
		speed = SHOOTER_WENCH_MOTOR_FULL_RELEASE_NEAR;
	}
	if (shooter->getTurns() <= setTurns) {
		shooter->setWenchMotor(speed);
	} else {
		shooter->setWenchMotor(-speed);
	}
}

bool ReleaseTension::IsFinished() {
	return shooter->getTurns() <= setTurns && (fabs(shooter->getTurns()
			- setTurns) < SHOOTER_WENCH_PAYOUT_TOLERANCE);
}

void ReleaseTension::End() {
	shooter->lastReleasePosition = setTurns;
	shooter->setWenchMotor(0);
}

void ReleaseTension::Interrupted() {
	shooter->lastReleasePosition = setTurns;
	shooter->setWenchMotor(0);
}
