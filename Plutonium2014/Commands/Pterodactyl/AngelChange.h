#ifndef __ANGEL_CHANGE_H
#define __ANGEL_CHANGE_H

#include "../../CommandBase.h"

/**
 *
 *
 * @author David ;)
 */
class AngelChange : public CommandBase {
private:
	float target;
	int stability;
	float tmpTarget;
	
	float angleThreshold;

	double brakeEngagedTime;
public:
	AngelChange(float target, float timeout =25.0);
	AngelChange *setTolerance(float tolerance);
	virtual void Initialize();
	virtual void Execute();
	virtual bool IsFinished();
	virtual void End();
	virtual void Interrupted();
};

#endif
