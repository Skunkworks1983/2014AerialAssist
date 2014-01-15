#ifndef __ANGEL_CHANGE_H
#define __ANGEL_CHANGE_H

#include "../../CommandBase.h"

/**
 *
 *
 * @author ExampleAuthor
 */
class AngelChange: public CommandBase {
public:
	AngelChange();
	virtual void Initialize();
	virtual void Execute();
	virtual bool IsFinished();
	virtual void End();
	virtual void Interrupted();
};

#endif
