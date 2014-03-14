#ifndef __FIRE_SHOOTER_INTERNAL_H
#define __FIRE_SHOOTER_INTERNAL_H

#include "../../../CommandBase.h"

/**
 *
 *
 * @author These are all david so I guess this is as well
 * DAVEEDq	
 */

class FireShooterInternal: public CommandGroup {
public:
	FireShooterInternal(bool autoArm = true);
	virtual void Initialize();
	virtual void End();
	virtual void Interrupted();
};

#endif
