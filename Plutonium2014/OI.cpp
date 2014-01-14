#include "OI.h"

OI::OI() {
	joystickLeft = new Joystick(1);
	joystickRight = new Joystick(2);
	// Process operator interface input here.
}

Joystick *OI::getJoystickLeft() {
	return joystickLeft;
}

Joystick *OI::getJoystickRight() {
	return joystickRight;
}
