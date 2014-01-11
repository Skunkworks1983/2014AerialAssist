#ifndef __COLLECT_H
#define __COLLECT_H

#include "../CommandBase.h"

/**
 *
 *
 * @author ExampleAuthor
 */
class Collect: public CommandBase {
public:
	Collect();
	virtual void Initialize();
	virtual void Execute();
	virtual bool IsFinished();
	virtual void End();
	virtual void Interrupted();
};

#endif
