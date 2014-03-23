#ifndef __GULP_H
#define __GULP_H

#include "../../CommandBase.h"

/**
 *
 *
 * @author David
 */
class Gulp: public CommandBase {
public:
	Gulp();
	~Gulp();
	virtual void Initialize();
	virtual void Execute();
	virtual bool IsFinished();
	virtual void End();
	virtual void Interrupted();
};

#endif

