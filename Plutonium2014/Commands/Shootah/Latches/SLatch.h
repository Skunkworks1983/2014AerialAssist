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
	Shootah::LatchPosition isLocked;
	double time;
	double bTime;
	
public:
	SLatch(Shootah::LatchPosition isLocked);
	virtual void Initialize();
	virtual void Execute();
	virtual bool IsFinished();
	virtual void End();
	virtual void Interrupted();
};

#endif
