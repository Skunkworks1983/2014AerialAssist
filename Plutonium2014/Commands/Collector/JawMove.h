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
	bool isUp;
public:
	JawMove(bool isUp);
	virtual void Initialize();
	virtual void Execute();
	virtual bool IsFinished();
	virtual void End();
	virtual void Interrupted();
};

#endif
