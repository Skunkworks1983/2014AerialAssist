#ifndef __DRAW_SHOOTER_BACK_H
#define __DRAW_SHOOTER_BACK_H

#include "../../../CommandBase.h"

/**
 *
 *
 * @author David
 */
class FullTension: public CommandBase {
public:
	FullTension();
	virtual void Initialize();
	virtual void Execute();
	virtual bool IsFinished();
	virtual void End();
	virtual void Interrupted();
};

#endif
