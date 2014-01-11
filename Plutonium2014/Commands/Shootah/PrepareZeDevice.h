#ifndef __PREPARE_ZE_DEVICE_H
#define __PREPARE_ZE_DEVICE_H

#include "../CommandBase.h"

/**
 *
 *
 * @author ExampleAuthor
 */
class PrepareZeDevice: public CommandBase {
public:
	PrepareZeDevice();
	virtual void Initialize();
	virtual void Execute();
	virtual bool IsFinished();
	virtual void End();
	virtual void Interrupted();
};

#endif
