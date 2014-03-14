#ifndef __RESET_SHOOTER_H
#define __RESET_SHOOTER_H

#include "../../CommandBase.h"

/**
 *
 *
 * @author These are all david so I guess this is as well
 * DAVEEDq	
 */

class ResetShooter: public CommandBase {
public:
	ResetShooter();
	virtual void Initialize();
	virtual void End();
	virtual void Interrupted();
	virtual void Execute();
	virtual bool IsFinished();
};

#endif
