#ifndef __DRAW_SHOOTER_H
#define __DRAW_SHOOTER_H

#include "../../CommandBase.h"

/**
 *
 *
 * @author These are all david so I guess this is as well
 * DAVEED
 */

class DrawShooter: public CommandGroup {
public:
	DrawShooter();
	virtual void Initialize();
	virtual void End();
};

#endif
