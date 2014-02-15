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
	JoystickButton *RollerRollOn;
	JoystickButton *RollerRollOff;
	JoystickButton *drawBack;
	JoystickButton *prepare;
	JoystickButton *shootGlatGlat;
	JoystickButton *armODeathBackward;
	JoystickButton *armODeathForward;
	float scale;

public:
	OI();
	Joystick *getJoystickLeft();
	Joystick *getJoystickRight();
	void registerButtonListeners();
	float getScale();
};

#endif
