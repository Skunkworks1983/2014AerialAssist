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
public:
	JawMove(Collector::JawState state);
	virtual void Initialize();
	virtual void Execute();
	virtual bool IsFinished();
	virtual void End();
	virtual void Interrupted();
};

#endif
