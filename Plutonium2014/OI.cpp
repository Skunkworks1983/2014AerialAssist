#include "OI.h"
#include "Commands/DriveBase/Shift.h"
#include "Buttons/PressedButtonScheduler.h"
#include "Commands/Collector/RollerRoll.h"
OI::OI() {
	joystickLeft = new Joystick(1);
	joystickRight = new Joystick(2);
	// Process operator interface input here.
	shiftButton = new JoystickButton(joystickLeft, 1);
	rollerOn = new JoystickButton(joystickRight, 2);
	rollerOff = new JoystickButton(joystickRight, 3);
}
void OI::registerButtonListeners() {
	Scheduler::GetInstance()->AddButton(new PressedButtonScheduler(false, shiftButton, new Shift(Shift::kToggle)));
	Scheduler::GetInstance()->AddButton(new PressedButtonScheduler(false, rollerOn, new RollerRoll(0.25)));
	Scheduler::GetInstance()->AddButton(new PressedButtonScheduler(false, rollerOff, new RollerRoll(0.0)));
}
Joystick *OI::getJoystickLeft() {
	return joystickLeft;
}

Joystick *OI::getJoystickRight() {
	return joystickRight;
}
