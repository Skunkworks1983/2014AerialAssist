#ifndef __SHOOTAH_H
#define __SHOOTAH_H
#include "Commands/Subsystem.h"
#include "WPILib.h"

/**
 *
 *
 * @author David
 */
class Shootah: public Subsystem {
private:
	// It's desirable that everything possible under private except
	// for methods that implement subsystem capabilities
public:
	Shootah();
	void InitDefaultCommand();
};

#endif
