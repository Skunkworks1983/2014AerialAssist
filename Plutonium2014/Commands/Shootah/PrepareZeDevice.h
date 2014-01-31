#ifndef __PREPARE_ZE_DEVICE_H
#define __PREPARE_ZE_DEVICE_H

#include "../../CommandBase.h"


/**
 *
 *
 * @author These are all david so I guess this is as well
 * DAVEED
 */
class PrepareZeDevice: public CommandBase {
private:
	float setpoint;
public:
	PrepareZeDevice(float setpoint);
	virtual void Initialize();
	virtual void Execute();
	virtual bool IsFinished();
	virtual void End();
	virtual void Interrupted();
};

#endif
