#include "OI.h"
#include "Robotmap.h"
#include "Buttons/Button.h"

#include "Utils/Buttons/CompositeButton.h"
#include "Utils/Buttons/OverridableButton.h"
#include "Utils/Buttons/AnalogRangeIOButton.h"

#include "Utils/Commands/CommandCanceler.h"

#include "Commands/DriveBase/Shift.h"
#include "Commands/Collector/RollerRoll.h"
#include "Commands/Collector/JawMove.h"
#include "Commands/Pterodactyl/AngelChange.h"
#include "Commands/Shootah/DrawZeDevice.h"
#include "Commands/Shootah/PrepareZeDevice.h"
#include "Commands/Shootah/FireZeMissle.h"
#include "Commands/Collector/Collect.h"
#include "Commands/Shootah/DrawShootahBack.h"
#include "Commands/Shootah/ReleaseTension.h"
#include "Commands/Collector/Pass.h"
#include "Commands/Collector/Catch.h"
#include "Commands/Shootah/ReadyShot.h"

#define JOYSTICK_OF_THINGS 0

#define START_STOP_COMMAND(btnA, cmd) {Command *command=cmd; btnA->WhenReleased(command); btnA->WhenPressed(new CommandCanceler(command));}

OI::OI() {
	joystickLeft = new Joystick(OI_JOYSTICK_LEFT);
	joystickRight = new Joystick(OI_JOYSTICK_RIGHT);
	// Process operator interface input here.
	shiftButton = new JoystickButton(joystickRight, 1);

#if JOYSTICK_OF_THINGS
	joystickButtonsThings = new Joystick(3);

	rollerOn = new JoystickButton(joystickRight, 3);
	rollerOff = new JoystickButton(joystickRight, 2);
	RollerRollOn = new JoystickButton(joystickLeft, 4);
	RollerRollOff = new JoystickButton(joystickLeft, 5);
	shootGlatGlat = new JoystickButton(joystickLeft, 1);

	armODeathZero = new JoystickButton(joystickButtonsThings, 6);
	armODeathThirty = new JoystickButton(joystickButtonsThings, 7);
	armODeathSixty = new JoystickButton(joystickButtonsThings, 11);
	armODeathNintey = new JoystickButton(joystickButtonsThings, 10);

	drawBack = new JoystickButton(joystickLeft, 2);
	prepare = new JoystickButton(joystickLeft, 3);

#endif
	catch1 = new DigitalIOButton(1);
	catch2 = new DigitalIOButton(3);
	collect = new DigitalIOButton(5);
	pass = new DigitalIOButton(7);

	angleFloor = new DigitalIOButton(4);
	angleLow = new DigitalIOButton(6);
	angleMed = new DigitalIOButton(8);
	angleHigh = new DigitalIOButton(13);
	angleCarry = new DigitalIOButton(15);

	fire = new DigitalIOButton(2);
	revCollector = new DigitalIOButton(9);
	jawToggle = new OverridableButton(new DigitalIOButton(12),new DigitalIOButton(11), false);
	manShootOvr = new DigitalIOButton(10);
	manAngleOvr = new DigitalIOButton(16);
	
	power3 = new AnalogRangeIOButton(OI_SHOOTER_POWER_PORT, 1.115-OI_ANALOG_TRESHOLD, 1.115+OI_ANALOG_TRESHOLD);
	power2 = new AnalogRangeIOButton(OI_SHOOTER_POWER_PORT, 1.677-OI_ANALOG_TRESHOLD, 1.677+OI_ANALOG_TRESHOLD);
	power1 = new AnalogRangeIOButton(OI_SHOOTER_POWER_PORT, 3.342-OI_ANALOG_TRESHOLD, 3.342+OI_ANALOG_TRESHOLD);
}
void OI::registerButtonListeners() {
#if JOYSTICK_OF_THINGS
	Scheduler::GetInstance()->AddButton(new PressedButtonScheduler(false, shiftButton,
					new Shift(Shift::kToggle)));
	//  Scheduler::GetInstance()->AddButton(new PressedButtonScheduler(false, rollerOn, new Collect()));
	//  Scheduler::GetInstance()->AddButton(new PressedButtonScheduler(false, rollerOff, new Collect()));
	Scheduler::GetInstance()->AddButton(new PressedButtonScheduler(false, RollerRollOn,
					new RollerRoll(1000)));
	Scheduler::GetInstance()->AddButton(new PressedButtonScheduler(false, RollerRollOff,
					new RollerRoll(0)));
	Scheduler::GetInstance()->AddButton(new PressedButtonScheduler(false, armODeathZero,
					new AngelChange(5)));
	Scheduler::GetInstance()->AddButton(new PressedButtonScheduler(false, armODeathThirty,
					new AngelChange(30)));
	Scheduler::GetInstance()->AddButton(new PressedButtonScheduler(false, armODeathSixty,
					new AngelChange(60)));
	Scheduler::GetInstance()->AddButton(new PressedButtonScheduler(false, armODeathNintey,
					new AngelChange(90)));

	Scheduler::GetInstance()->AddButton(new PressedButtonScheduler(false, shootGlatGlat, new FireZeMissle()));
	drawBack->WhenPressed(new DrawZeDevice());
	prepare->WhenPressed(new PrepareZeDevice(1.0f));
#endif
	// Real OI!
	angleFloor->WhenPressed(new AngelChange(0));
	angleLow->WhenPressed(new AngelChange(60));
	angleMed->WhenPressed(new AngelChange(80));
	angleHigh->WhenPressed(new AngelChange(90));
	angleCarry->WhenPressed(new AngelChange(90));
	
	revCollector->WhenPressed(new RollerRoll(0));
	START_STOP_COMMAND(collect, new Collect());
	pass->WhenPressed(new Pass());
	catch1->WhenPressed(new Catch(90));
	catch2->WhenPressed(new Catch(30));

	fire->WhenPressed(new FireZeMissle());

	jawToggle->WhenPressed(new JawMove(true));
	jawToggle->WhenReleased(new JawMove(false));
	
	power1->WhenPressed(new ReadyShot(SHOOTER_POWER_TURNS_1));
	power2->WhenPressed(new ReadyShot(SHOOTER_POWER_TURNS_2));
	power3->WhenPressed(new ReadyShot(SHOOTER_POWER_TURNS_3));
}
Joystick *OI::getJoystickLeft() {
	return joystickLeft;
}

Joystick *OI::getJoystickRight() {
	return joystickRight;
}
