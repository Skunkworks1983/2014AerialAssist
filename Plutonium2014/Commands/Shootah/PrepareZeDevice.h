#ifndef __PREPARE_ZE_DEVICE_H
#define __PREPARE_ZE_DEVICE_H

#include "../../CommandBase.h"

/**
 *
 *
 * @author These are all david so I guess this is as well
 * DAVEED
 */

class PrepareZeDevice: public CommandGroup {
public:
	PrepareZeDevice(float setTurns);
	virtual void Initialize();
	virtual void End();
};

#endif
