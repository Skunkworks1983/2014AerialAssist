#ifndef __READY_SHOT_H
#define __READY_SHOT_H

#include "../../CommandBase.h"

/**
 *
 *
 * @author These are all david so I guess this is as well
 * DAVEED
 */

class ReadyShot : public CommandGroup {
public:
	ReadyShot(float setTurns, float angle = -1);
	virtual void Initialize();
	virtual void End();
	virtual void Interrupted();
};

#endif
