#include "OI.h"
#include "Commands/Drivebase/Shift.h"
#include "Buttons/PressedButtonScheduler.h"
OI::OI() {
	joystickLeft = new Joystick(1);
	joystickRight = new Joystick(2);
	// Process operator interface input here.
	shiftButton = new JoystickButton(joystickLeft, 1);
}
void OI::registerButtonListeners() {
	Scheduler::GetInstance()->AddButton(new PressedButtonScheduler(false, shiftButton, new Shift(Shift::kToggle)));
}
Joystick *OI::getJoystickLeft() {
	return joystickLeft;
}

Joystick *OI::getJoystickRight() {
	return joystickRight;
}
