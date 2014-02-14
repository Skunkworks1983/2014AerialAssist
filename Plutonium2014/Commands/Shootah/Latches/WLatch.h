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
	Shootah::LatchPosition state;
	double time;
	double bTime;
	
public:
	WLatch(Shootah::LatchPosition state);
	virtual void Initialize();
	virtual void Execute();
	virtual bool IsFinished();
	virtual void End();
	virtual void Interrupted();
};

#endif
