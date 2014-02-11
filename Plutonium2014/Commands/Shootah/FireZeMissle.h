#ifndef __FIRE_ZE_MISSLE_H
#define __FIRE_ZE_MISSLE_H

#include "../../CommandBase.h"

/**
 *
 *
 * @author These are all david so I guess this is as well
 * DAVEED
 */

class FireZeMissle: public CommandGroup {
public:
	FireZeMissle();
	virtual void Initialize();
	virtual void End();
};

#endif
