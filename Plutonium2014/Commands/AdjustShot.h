#ifndef __ADJUST_SHOT_H
#define __ADJUST_SHOT_H

#include "../CommandBase.h"

/**
 *
 *
 * @author ExampleAuthor
 */
class AdjustShot: public CommandBase {
public:
	AdjustShot ();
	virtual void Initialize();
	virtual void Execute();
	virtual bool IsFinished();
	virtual void End();
	virtual void Interrupted();
};

#endif
