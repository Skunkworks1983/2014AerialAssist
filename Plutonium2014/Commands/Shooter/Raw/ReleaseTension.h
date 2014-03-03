#ifndef __RELEASE_TENSION_H
#define __RELEASE_TENSION_H

#include "../../../CommandBase.h"


/**
 *
 *
 * @author These are all david so I guess this is as well
 * DAVEED
 */
class ReleaseTension: public CommandBase {
private:
	float setTurns;
	bool isDone;

public:
	ReleaseTension(float setTurns);
	virtual void Initialize();
	virtual void Execute();
	virtual bool IsFinished();
	virtual void End();
	virtual void Interrupted();
	static int runCount;
	int fHandle;
};

#endif
