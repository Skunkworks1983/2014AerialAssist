#ifndef __SHIFT_H
#define __SHIFT_H

#include "../CommandBase.h"

/**
 *
 *
 * @author ExampleAuthor
 */
class Shift: public CommandBase {
public:
	Shift();
	virtual void Initialize();
	virtual void Execute();
	virtual bool IsFinished();
	virtual void End();
	virtual void Interrupted();
};

#endif
