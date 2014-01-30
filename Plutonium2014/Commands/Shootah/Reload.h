#ifndef __RELOAD_H
#define __RELOAD_H

#include "../../CommandBase.h"

/**
 *
 *
 * @author David
 */
class Reload: CommandGroup {
public:
	Reload(float setpoint);
	~Reload();
};

#endif
