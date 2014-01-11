#ifndef __SHOOT_H
#define __SHOOT_H

#include "../CommandBase.h"

/**
 *
 *
 * @author ExampleAuthor
 */
class Shoot: public CommandBase {
public:
	Shoot();
	virtual void Initialize();
	virtual void Execute();
	virtual bool IsFinished();
	virtual void End();
	virtual void Interrupted();
};

#endif
