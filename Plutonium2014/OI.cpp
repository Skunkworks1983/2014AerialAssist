#include "OI.h"
#include "Commands/DriveBase/Shift.h"
#include "Buttons/PressedButtonScheduler.h"
#include "Commands/Collector/RollerRoll.h"
#include "Commands/Pterodactyl/AngelChange.h"
#include "Commands/Shootah/DrawZeDevice.h"
#include "Commands/Shootah/PrepareZeDevice.h"
#include "Commands/Shootah/FireZeMissle.h"
#include "Commands/Collector/Collect.h"

OI::OI() {
	joystickLeft = new Joystick(1);
	joystickRight = new Joystick(2);
	// Process operator interface input here.
	shiftButton = new JoystickButton(joystickRight, 1);
	drawBack = new JoystickButton(joystickLeft, 2);
	prepare = new JoystickButton(joystickLeft, 3);
	
	rollerOn = new JoystickButton(joystickRight, 3);
	rollerOff = new JoystickButton(joystickRight, 2);
	//armODeathForward = new JoystickButton(joystickLeft, 4);
	//armODeathBackward = new JoystickButton(joystickLeft, 5);
	shootGlatGlat = new JoystickButton(joystickLeft, 1);
}
void OI::registerButtonListeners() {
	//Scheduler::GetInstance()->AddButton(new PressedButtonScheduler(false, shiftButton, new Shift(Shift::kToggle)));
	Scheduler::GetInstance()->AddButton(new PressedButtonScheduler(false, rollerOn, new Collect()));
	Scheduler::GetInstance()->AddButton(new PressedButtonScheduler(false, rollerOff, new Collect()));
	//Scheduler::GetInstance()->AddButton(new PressedButtonScheduler(false, armODeathForward, new AngelChange(0.16)));
	//Scheduler::GetInstance()->AddButton(new PressedButtonScheduler(false, armODeathBackward, new AngelChange(-0.16)));
	Scheduler::GetInstance()->AddButton(new PressedButtonScheduler(false, drawBack, new DrawZeDevice()));
	Scheduler::GetInstance()->AddButton(new PressedButtonScheduler(false, prepare, new PrepareZeDevice(7.0f)));
	Scheduler::GetInstance()->AddButton(new PressedButtonScheduler(false, shootGlatGlat, new FireZeMissle()));
}
Joystick *OI::getJoystickLeft() {
	return joystickLeft;
}

Joystick *OI::getJoystickRight() {
	return joystickRight;
}
