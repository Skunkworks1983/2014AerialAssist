#ifndef __FIRE_ZE_MISSLE_H
#define __FIRE_ZE_MISSLE_H

#include "../../CommandBase.h"

/**
 *
 *
 * @author David (for really tho)
 */
class FireZeMissle: public CommandBase {
public:
	FireZeMissle();
	virtual void Initialize();
	virtual void Execute();
	virtual bool IsFinished();
	virtual void End();
	virtual void Interrupted();
};

#endif
