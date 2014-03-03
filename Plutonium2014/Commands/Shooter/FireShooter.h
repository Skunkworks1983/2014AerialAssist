#ifndef __FIRE_SHOOTER_H
#define __FIRE_SHOOTER_H

#include "../../CommandBase.h"

/**
 *
 *
 * @author These are all david so I guess this is as well
 * DAVEEDq	
 */

class FireShooter: public CommandGroup {
public:
	FireShooter();
	virtual void Initialize();
	virtual void End();
	virtual void Interrupted();
};

#endif
