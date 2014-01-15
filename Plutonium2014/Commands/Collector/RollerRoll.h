#ifndef __ROLLER_ROLL_H
#define __ROLLER_ROLL_H

#include "../../CommandBase.h"

/**
 *
 *
 * @author ExampleAuthor
 */
class RollerRoll: public CommandBase {
public:
	RollerRoll();
	virtual void Initialize();
	virtual void Execute();
	virtual bool IsFinished();
	virtual void End();
	virtual void Interrupted();
};

#endif
