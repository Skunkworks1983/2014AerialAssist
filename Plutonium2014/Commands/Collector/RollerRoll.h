#ifndef __ROLLER_ROLL_H
#define __ROLLER_ROLL_H

#include "../../CommandBase.h"

/**
 *
 *
 * @author Ross Bajocich
 */
class RollerRoll: public CommandBase {
private:
	float speed;
public:
	RollerRoll(float speed);
	virtual void Initialize();
	virtual void Execute();
	virtual bool IsFinished();
	virtual void End();
	virtual void Interrupted();
};

#endif
