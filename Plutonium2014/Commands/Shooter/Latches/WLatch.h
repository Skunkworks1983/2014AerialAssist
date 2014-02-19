#ifndef __W_LATCH_H
#define __W_LATCH_H

#include "../../../CommandBase.h"

/**
 *
 *
 * @author David (for really tho)
 */
class Time;

class WLatch: public CommandBase {
private:
	Shooter::LatchPosition state;
	double time;
	double bTime;
	
public:
	WLatch(Shooter::LatchPosition state);
	virtual void Initialize();
	virtual void Execute();
	virtual bool IsFinished();
	virtual void End();
	virtual void Interrupted();
};

#endif
