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
	JoystickButton *drawBack;
	JoystickButton *prepare;
	float scale;
	
public:
	OI();
	Joystick *getJoystickLeft();
	Joystick *getJoystickRight();
	void registerButtonListeners();
	float getScale();
};

#endif
