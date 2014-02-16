#ifndef OI_H
#define OI_H

#include "WPILib.h"

class OI {
private:
	Joystick *joystickLeft;
	Joystick *joystickRight;
	Joystick *joystickButtonsThings;

	JoystickButton *shiftButton;
	JoystickButton *rollerOn;
	JoystickButton *rollerOff;
	JoystickButton *RollerRollOn;
	JoystickButton *RollerRollOff;
	JoystickButton *drawBack;
	JoystickButton *prepare;
	JoystickButton *shootGlatGlat;
	JoystickButton *armODeathZero;
	JoystickButton *armODeathThirty;
	JoystickButton *armODeathSixty;
	JoystickButton *armODeathNintey;
	float scale;

public:
	OI();
	Joystick *getJoystickLeft();
	Joystick *getJoystickRight();
	void registerButtonListeners();
	float getScale();
};

#endif
