#ifndef __AUTO_DRIVE_DISTANCE_H
#define __AUTO_DRIVE_DISTANCE_H

#include "../CommandBase.h"

/**
 *
 *
 * @author ExampleAuthor
 */
class AutoDriveDistance: public CommandBase {
public:
	AutoDriveDistance();
	virtual void Initialize();
	virtual void Execute();
	virtual bool IsFinished();
	virtual void End();
	virtual void Interrupted();
};

#endif
