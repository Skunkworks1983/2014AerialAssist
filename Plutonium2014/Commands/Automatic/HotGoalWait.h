#ifndef HOT_GOAL_WAIT_H
#define HOT_GOAL_WAIT_H

// Backend
#include "../../CommandBase.h"
#include "WPILib.h"

class HotGoalWait : public CommandBase {
private:
	ITable *table;
public:
	HotGoalWait();
	virtual void Initialize();
	virtual void Execute();
	virtual bool IsFinished();
	virtual void End();
	virtual void Interrupted();
};
#endif
