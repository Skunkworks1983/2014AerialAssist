#include "AutoDriveDistance.h"
// CSTDLIB
#include <math.h>

// Utils
#include "../../Utils/Math.h"

// Backend
#include "../../Robotmap.h"
#include "../../CommandBase.h"

AutoDriveDistance::AutoDriveDistance(float targetDistance, float tStable,
		float tThresh) :
	CommandBase(CommandBase::createNameFromFloat("AutoDriveDistance",
			targetDistance)) {
	Requires(driveBase);
	this->targetDistance = targetDistance;
	this->tStable = tStable;
	this->threshold = tThresh;
	this->reset = true;
	this->minSpeed = AUTO_DRIVE_DIST_SPEED_MIN;
	this->maxSpeed = AUTO_DRIVE_DIST_SPEED_MAX;

	//Reset things
	this->stability = 0;
	this->rightDistanceRemaining = 1e9;
	this->leftDistanceRemaining = 1e9;
}

AutoDriveDistance *AutoDriveDistance::setResetEncoder(bool r) {
	this->reset = r;
	return this;
}

AutoDriveDistance *AutoDriveDistance::setOutputRange(float min, float max) {
	this->minSpeed = min;
	this->maxSpeed = max;
	return this;
}

void AutoDriveDistance::Initialize() {
	if (!reset) {
		targetDistance = ((targetDistance - driveBase->getLeftEncoder()->GetDistance()) + (targetDistance
				- driveBase->getRightEncoder()->GetDistance())) / 2.0;
	}
	driveBase->encoderReset();
	driveBase->setDriveGear(DriveBase::kHigh);
	stability = 0;
}

void AutoDriveDistance::Execute() {
	leftDistanceRemaining = targetDistance - driveBase->getLeftEncoder()->GetDistance();
	rightDistanceRemaining = targetDistance - driveBase->getRightEncoder()->GetDistance();
	float lSpeed = getSpeedFor(leftDistanceRemaining,
			driveBase->getLeftEncoder()->GetRate());
	float rSpeed = getSpeedFor(rightDistanceRemaining,
			driveBase->getRightEncoder()->GetRate());
	lSpeed *= fmax(fmin( (AUTO_DRIVE_DIST_CATCHUP - (rightDistanceRemaining - leftDistanceRemaining))
			/ AUTO_DRIVE_DIST_CATCHUP, 1.0), 0.0);
	rSpeed *= fmax(fmin( (AUTO_DRIVE_DIST_CATCHUP - (leftDistanceRemaining - rightDistanceRemaining))
			/ AUTO_DRIVE_DIST_CATCHUP, 1.0), 0.0);
	driveBase->setSpeed(lSpeed, rSpeed);
	if ((fabs(leftDistanceRemaining) <= threshold)
			|| (fabs(rightDistanceRemaining) <= threshold)) {
		stability++;
	} else {
		stability = 0;
	}
}

float AutoDriveDistance::getSpeedFor(float distanceRemaining, float speed) {
	if (fabs(distanceRemaining) <= threshold) {
		return 0.0; //-speed / AUTO_DRIVE_DIST_SLOW_DOWN;
	}

	float speedScaleFactor = fabs(distanceRemaining)
			/ AUTO_DRIVE_DIST_SLOW_DOWN;
	return fmin(maxSpeed, ((maxSpeed - minSpeed) * speedScaleFactor) + minSpeed)
			* fsign(distanceRemaining);
}

bool AutoDriveDistance::IsFinished() {
	return stability >= tStable;
}

void AutoDriveDistance::End() {
	driveBase->setSpeed(0.0, 0.0);
}

void AutoDriveDistance::Interrupted() {
	driveBase->setSpeed(0.0, 0.0);
}
