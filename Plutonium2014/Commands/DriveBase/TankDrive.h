#ifndef __TANK_DRIVE_H
#define __TANK_DRIVE_H

#include "../../CommandBase.h"

/**
 *
 *
 * @author David
 */
class TankDrive: public CommandBase {
public:
	TankDrive();
	virtual void Initialize();
	virtual void Execute();
	virtual bool IsFinished();
	virtual void End();
	virtual void Interrupted();
};

#endif
