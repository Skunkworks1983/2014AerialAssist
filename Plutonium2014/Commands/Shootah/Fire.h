#ifndef __FIRE_H
#define __FIRE_H

#include "../../CommandBase.h"

/**
 *
 *
 * @author ExampleAuthor
 */
class Fire: public CommandBase {
public:
	Fire();
	virtual void Initialize();
	virtual void Execute();
	virtual bool IsFinished();
	virtual void End();
	virtual void Interrupted();
};

#endif
