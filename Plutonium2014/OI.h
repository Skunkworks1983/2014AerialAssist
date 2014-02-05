#ifndef OI_H
#define OI_H

#include "WPILib.h"

class OI {
private:
	Joystick *joystickLeft;
	Joystick *joystickRight;
	
	JoystickButton *shiftButton;
	JoystickButton *rollerOn;
	JoystickButton *rollerOff;
	JoystickButton *armODeathForward;
	JoystickButton *armODeathBackward;
	JoystickButton *armOStop;
	float scale;
	
public:
	OI();
	Joystick *getJoystickLeft();
	Joystick *getJoystickRight();
	void registerButtonListeners();
	float getScale();
};

#endif
