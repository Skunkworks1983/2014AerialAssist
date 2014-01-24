#ifndef __DRAW_ZE_DEVICE_H
#define __DRAW_ZE_DEVICE_H

#include "../../CommandBase.h"

/**
 *
 *
 * @author David
 */
class DrawZeDevice: public CommandBase {
public:
	DrawZeDevice();
	virtual void Initialize();
	virtual void Execute();
	virtual bool IsFinished();
	virtual void End();
	virtual void Interrupted();
};

#endif
