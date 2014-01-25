#ifndef __AUTO_DRIVE_DISTANCE_H
#define __AUTO_DRIVE_DISTANCE_H

#include "../../CommandBase.h"
#include "../../Subsystems/DriveBase.h"
#include "../../Robotmap.h"

/**
 * @brief Uses the DriveBase and it's encoders to drive a certain distance.
 * 
 * This command requires an exclusive lock on the DriveBase, as well as encoders.
 * @author Owen Mattson
 */
class AutoDriveDistance: public CommandBase {
private:
	float minSpeed;
	float maxSpeed;
	float threshold;
	float tStable;
	float targetDistance;
	float leftDistanceRemaining;
	float rightDistanceRemaining;
	int stability;
	bool reset;
	/**
	 * @brief Calculates the motor speed for the given remaining distance.
	 * 
	 * @param remainingDistance the remaining distance, in inches
	 * @return the motor speed
	 */
	float getSpeedFor(float remainingDistance, float speed);
public:
	/**
	 * @brief Creates a command to drive a certain distance.
	 * 
	 * Creates a drive distance command that will drive the specified distance,
	 * then stop, in a direction specified by the sign.
	 * @param targetDistance the target distance, in inches
	 */
	AutoDriveDistance(float targetDistance,
			float tStable = AUTO_DRIVE_DIST_STABILITY,
			float tThreshold = AUTO_DRIVE_DIST_THRESHOLD);
	AutoDriveDistance *setResetEncoder(bool reset);
	AutoDriveDistance *AutoDriveDistance::setOutputRange(float min, float max);
	virtual void Initialize();
	virtual void Execute();
	virtual bool IsFinished();
	virtual void End();
	virtual void Interrupted();
};
#endif

