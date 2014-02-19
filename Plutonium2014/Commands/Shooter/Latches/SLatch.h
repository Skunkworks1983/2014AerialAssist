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
	Shooter::LatchPosition isLocked;
	double time;
	double bTime;
	
public:
	SLatch(Shooter::LatchPosition isLocked);
	virtual void Initialize();
	virtual void Execute();
	virtual bool IsFinished();
	virtual void End();
	virtual void Interrupted();
};

#endif
