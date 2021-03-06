#include "TurnDegree.h"
// CSTDLIB
#include <math.h>

// Utils
#include "../../Utils/Math.h"

// Backend
#include "../../Robotmap.h"

TurnDegree::TurnDegree(float targetAngle) :
	CommandBase(CommandBase::createNameFromFloat("TurnDegree", targetAngle)) {
	Requires(driveBase);
	this->targetAngle = targetAngle;
	this->angleRemaining = 0;
}

void TurnDegree::Initialize() {
//	driveBase->getGyro()->Reset();
	angleRemaining = 0;
}

void TurnDegree::Execute() {
//	angleRemaining = targetAngle - driveBase->getGyro()->GetAngle();

	float turnScaleFactor = fabs(angleRemaining) / AUTO_TURN_SLOW_DOWN;

	float turnSpeed = fmin(AUTO_TURN_SPEED_MAX,
			(AUTO_TURN_SPEED_RANGE * turnScaleFactor) + AUTO_TURN_SPEED_MIN)
			* fsign(angleRemaining);
	if (fabs(angleRemaining) <= AUTO_TURN_GYRO_THRESHOLD) {
		turnSpeed = 0;
	}

	driveBase->setSpeed(turnSpeed, -turnSpeed);
}

bool TurnDegree::IsFinished() {
	return fabs(angleRemaining) <= AUTO_TURN_GYRO_THRESHOLD;
}

void TurnDegree::End() {
	driveBase->setSpeed(0.0, 0.0);
}

void TurnDegree::Interrupted() {
	driveBase->setSpeed(0.0, 0.0);
}

