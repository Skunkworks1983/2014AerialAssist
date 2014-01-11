#ifndef __CATCH_H
#define __CATCH_H

#include "../CommandBase.h"

/**
 *
 *
 * @author ExampleAuthor
 */
class Catch: public CommandBase {
public:
	Catch();
	virtual void Initialize();
	virtual void Execute();
	virtual bool IsFinished();
	virtual void End();
	virtual void Interrupted();
};

#endif
