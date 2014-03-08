#ifndef __JAW_MOVE_H
#define __JAW_MOVE_H

#include "../../CommandBase.h"

/**
 *
 *
 * @author Ross Bajocich
 */
class JawMove: public CommandBase {
private:
	Collector::JawState state;
	bool killIt;
public:
	JawMove(Collector::JawState state, float timeout = 0.125);
	virtual void Initialize();
	virtual void Execute();
	virtual bool IsFinished();
	virtual void End();
	virtual void Interrupted();
};

#endif
