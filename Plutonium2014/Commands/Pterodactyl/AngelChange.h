#ifndef __ANGEL_CHANGE_H
#define __ANGEL_CHANGE_H

#include "../../CommandBase.h"

/**
 *
 *
 * @author David ;)
 */
class AngelChange: public CommandBase {
private:
	float target;
	int stability;
	float lastPosition;
public:
	AngelChange(float target);
	virtual void Initialize();
	virtual void Execute();
	virtual bool IsFinished();
	virtual void End();
	virtual void Interrupted();
};

#endif
