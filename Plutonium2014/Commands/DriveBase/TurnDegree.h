#ifndef __TURN_DEGREE_H
#define __TURN_DEGREE_H

#include "../../CommandBase.h"
#include "../../Subsystems/DriveBase.h"
#include "../../Robotmap.h"

/**
 * @brief Uses the DriveBase and it's encoders to turn a certain angle.
 * 
 * This command requires an exclusive lock on the DriveBase, as well as encoders.
 * @author David (yes)
 */
class TurnDegree: public CommandBase {
private:
	float targetAngle;
	float angleRemaining;
public:
	TurnDegree(float targetDistance);
	virtual void Initialize();
	virtual void Execute();
	virtual bool IsFinished();
	virtual void End();
	virtual void Interrupted();
};
#endif

