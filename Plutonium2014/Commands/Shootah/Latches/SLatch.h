#ifndef __S_LATCH_H
#define __S_LATCH_H

#include "../../../CommandBase.h"

/**
 *
 *
 * @author David (for really tho)
 */
class SLatch: public CommandBase {
private:
	bool isLocked;
	double time;
	double bTime;
	
public:
	SLatch(bool isLocked);
	virtual void Initialize();
	virtual void Execute();
	virtual bool IsFinished();
	virtual void End();
	virtual void Interrupted();
};

#endif
