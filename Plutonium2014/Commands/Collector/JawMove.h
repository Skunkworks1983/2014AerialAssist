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
	bool state;
public:
	JawMove(bool state);
	virtual void Initialize();
	virtual void Execute();
	virtual bool IsFinished();
	virtual void End();
	virtual void Interrupted();
};

#endif
