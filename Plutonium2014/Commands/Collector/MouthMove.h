#ifndef __MOUTH_MOVE_H
#define __MOUTH_MOVE_H

#include "../CommandBase.h"

/**
 *
 *
 * @author ExampleAuthor
 */
class MouthMove: public CommandBase {
public:
	MouthMove();
	virtual void Initialize();
	virtual void Execute();
	virtual bool IsFinished();
	virtual void End();
	virtual void Interrupted();
};

#endif
