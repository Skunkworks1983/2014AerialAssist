#ifndef __DRAW_ZE_DEVICE_H
#define __DRAW_ZE_DEVICE_H

#include "../../CommandBase.h"

/**
 *
 *
 * @author These are all david so I guess this is as well
 * DAVEED
 */

class DrawZeDevice: public CommandGroup {
public:
	DrawZeDevice();
	virtual void Initialize();
	virtual void End();
};

#endif
