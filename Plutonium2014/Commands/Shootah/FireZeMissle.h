#ifndef __FIRE_H
#define __FIRE_H

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
