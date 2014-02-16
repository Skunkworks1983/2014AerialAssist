#include "OI.h"
#include "Robotmap.h"
#include "Commands/DriveBase/Shift.h"
#include "Buttons/PressedButtonScheduler.h"
#include "Commands/Collector/RollerRoll.h"
#include "Commands/Pterodactyl/AngelChange.h"
#include "Commands/Shootah/DrawZeDevice.h"
#include "Commands/Shootah/PrepareZeDevice.h"
#include "Commands/Shootah/FireZeMissle.h"
#include "Commands/Collector/Collect.h"
#include "Commands/Shootah/DrawShootahBack.h"
#include "Commands/Shootah/ReleaseTension.h"

OI::OI() {
	joystickLeft = new Joystick(OI_JOYSTICK_LEFT);
	joystickRight = new Joystick(OI_JOYSTICK_RIGHT);
	joystickButtonsThings = new Joystick(3);
	// Process operator interface input here.
	shiftButton = new JoystickButton(joystickRight, 1);
	drawBack = new JoystickButton(joystickLeft, 2);
	prepare = new JoystickButton(joystickLeft, 3);

	rollerOn = new JoystickButton(joystickRight, 3);
	rollerOff = new JoystickButton(joystickRight, 2);
	RollerRollOn = new JoystickButton(joystickLeft, 4);
	RollerRollOff = new JoystickButton(joystickLeft, 5);
	shootGlatGlat = new JoystickButton(joystickLeft, 1);

	armODeathZero = new JoystickButton(joystickButtonsThings, 6);
	armODeathThirty = new JoystickButton(joystickButtonsThings, 7);
	armODeathSixty = new JoystickButton(joystickButtonsThings, 11);
	armODeathNintey = new JoystickButton(joystickButtonsThings, 10);
}
void OI::registerButtonListeners() {
	Scheduler::GetInstance()->AddButton(new PressedButtonScheduler(false, shiftButton,
			new Shift(Shift::kToggle)));
	//  Scheduler::GetInstance()->AddButton(new PressedButtonScheduler(false, rollerOn, new Collect()));
	//  Scheduler::GetInstance()->AddButton(new PressedButtonScheduler(false, rollerOff, new Collect()));
	Scheduler::GetInstance()->AddButton(new PressedButtonScheduler(false, RollerRollOn,
			new RollerRoll(1000)));
	Scheduler::GetInstance()->AddButton(new PressedButtonScheduler(false, RollerRollOff,
			new RollerRoll(-1000)));

	Scheduler::GetInstance()->AddButton(new PressedButtonScheduler(false, armODeathZero,
			new AngelChange(5)));
	Scheduler::GetInstance()->AddButton(new PressedButtonScheduler(false, armODeathThirty,
			new AngelChange(30)));
	Scheduler::GetInstance()->AddButton(new PressedButtonScheduler(false, armODeathSixty,
			new AngelChange(60)));
	Scheduler::GetInstance()->AddButton(new PressedButtonScheduler(false, armODeathNintey,
			new AngelChange(90)));

	Scheduler::GetInstance()->AddButton(new PressedButtonScheduler(false, drawBack, new DrawZeDevice()));
	Scheduler::GetInstance()->AddButton(new PressedButtonScheduler(false, prepare,
			new PrepareZeDevice(1.0f)));
	Scheduler::GetInstance()->AddButton(new PressedButtonScheduler(false, shootGlatGlat, new FireZeMissle()));
}
Joystick *OI::getJoystickLeft() {
	return joystickLeft;
}

Joystick *OI::getJoystickRight() {
	return joystickRight;
}
