#ifndef __AUTO_SHIFT_H
#define __AUTO_SHIFT_H

#include "../../CommandBase.h"

/**
 *
 *
 * @author David
 */
class AutoShift: public CommandBase {
private:
	int loopCount;
public:
	virtual void Initialize();
	virtual void Execute();
	virtual bool IsFinished();
	virtual void End();
	virtual void Interrupted();
};

#endif
