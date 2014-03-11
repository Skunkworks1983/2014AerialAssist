#ifndef __PNEUMATICS_H
#define __PNEUMATICS_H
#include "Commands/Subsystem.h"


class Relay;
class DigitalInput;
/**
 *
 *
 * @author David
 */
class Pneumatics: public Subsystem {
private:
	// It's desirable that everything possible under private except
	// for methods that implement subsystem capabilities
	DigitalInput *pressureSwitch;
	Relay *relay;
	
public:
	Pneumatics();
	void InitDefaultCommand();
	void setState(bool state);
	bool isBelowPressure();
	bool isCompressorOn();
};

#endif
