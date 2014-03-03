#ifndef __PREPARE_SHOOTER_H
#define __PREPARE_SHOOTER_H

#include "../../CommandBase.h"

/**
 *
 *
 * @author These are all david so I guess this is as well
 * DAVEED
 */

class PrepareShooter: public CommandGroup {
public:
	PrepareShooter(float setTurns);
	virtual void Initialize();
	virtual void End();
};

#endif
