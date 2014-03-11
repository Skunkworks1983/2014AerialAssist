#ifndef __FIRE_SHOOTER_H
#define __FIRE_SHOOTER_H

#include "../../CommandBase.h"

/**
 *
 *
 * @author These are all david so I guess this is as well
 * DAVEEDq	
 */

class FireShooter: public CommandBase {
public:
	FireShooter();
	virtual void Initialize();
	virtual void End();
	virtual void Interrupted();
	virtual void Execute();
	virtual bool IsFinished();
};

#endif
