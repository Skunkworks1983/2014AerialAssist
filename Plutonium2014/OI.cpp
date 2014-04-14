#include "OI.h"
#include "Robotmap.h"
#include "ShotTuning.h"
#include "Buttons/Button.h"

#include "Utils/Buttons/CompositeButton.h"
#include "Utils/Buttons/OverridableButton.h"
#include "Utils/Buttons/AnalogRangeIOButton.h"

#include "Utils/Commands/CommandCanceler.h"
#include "Utils/Commands/CommandStarter.h"

#include "Commands/DriveBase/Shift.h"
#include "Commands/Collector/RollerRoll.h"
#include "Commands/Collector/JawMove.h"
#include "Commands/Pterodactyl/AngelChange.h"
#include "Commands/Shooter/DrawShooter.h"
#include "Commands/Shooter/PrepareShooter.h"
#include "Commands/Shooter/FireShooter.h"
#include "Commands/Shooter/ResetShooter.h"
#include "Commands/Collector/Collect.h"
#include "Commands/Collector/Pass.h"
#include "Commands/Collector/Catch.h"
#include "Commands/Shooter/ReadyShot.h"

#include "Commands/Command.h"
#include "Commands/Collector/Gulp.h"

#include <math.h>

#define START_STOP_COMMAND(btnA, cmd, sleep) {Command *command=cmd; btnA->WhenReleased(command); btnA->WhenPressed(new CommandCanceler(command, sleep));}

OI::OI() {
	joystickLeft = new Joystick(OI_JOYSTICK_LEFT);
	joystickRight = new Joystick(OI_JOYSTICK_RIGHT);
	// Process operator interface input here.
	shiftButton = new JoystickButton(joystickLeft, 1);
	collectButton = new CompositeButton(new JoystickButton(joystickRight, 1),NULL,CompositeButton::kNOT);

	catch1 = new DigitalIOButton(1);
	resetShooter = new DigitalIOButton(3);
	collect = new DigitalIOButton(5);
	pass = new DigitalIOButton(7);

	angleFloor = new DigitalIOButton(4);
	angleLow = new DigitalIOButton(6);
	angleMed = new DigitalIOButton(8);
	shotTruss = new DigitalIOButton(13);
	startConfig = new DigitalIOButton(15);

	fire = new DigitalIOButton(2);
	revCollector = new DigitalIOButton(9);
	jawToggle = new OverridableButton(new DigitalIOButton(12),
			new DigitalIOButton(11), false);
	preventShooterArming = new DigitalIOButton(10);
	manAngleOvr = new DigitalIOButton(16);
	manPowerOvr = new DigitalIOButton(14);

	shotNear = new AnalogRangeIOButton(OI_SHOOTER_POWER_PORT,
			1.115 - OI_ANALOG_TRESHOLD, 1.115 + OI_ANALOG_TRESHOLD);
	shotSteep = new AnalogRangeIOButton(OI_SHOOTER_POWER_PORT,
			1.677 - OI_ANALOG_TRESHOLD, 1.677 + OI_ANALOG_TRESHOLD);
	power1 = new AnalogRangeIOButton(OI_SHOOTER_POWER_PORT,
			3.342 - OI_ANALOG_TRESHOLD, 3.342 + OI_ANALOG_TRESHOLD);
}
void OI::registerButtonListeners() {
	// Drivebase
	shiftButton->WhenPressed(new Shift(Shift::kLow));
	shiftButton->WhenReleased(new Shift(Shift::kHigh));

	// Pterodactyl Angle
	angleFloor->WhenPressed(new AngelChange(0));
	angleLow->WhenPressed(new AngelChange(30));//75));
	angleMed->WhenPressed(new AngelChange(84));//90));

	CommandGroup *startCfgCmd = new CommandGroup();
	startCfgCmd->AddSequential(new AngelChange(111.5));
	startCfgCmd->AddParallel(new JawMove(Collector::kClosed));
	startConfig->WhenPressed(startCfgCmd);

	// Collector rollers
	revCollector->WhenPressed(new Gulp());
	//new RollerRoll(-COLLECTOR_ROLLER_INTAKE_SET_POINT));
	START_STOP_COMMAND(collect, new Collect(), 1);
	START_STOP_COMMAND(collectButton, new Collect(), 1);

	// Jaw Operations
	pass->WhenPressed(new Pass());
	catch1->WhenPressed(new Catch(90));

	// Shooter operations
	fire->WhenReleased(new FireShooter());
	//fire->WhenPressed(new CommandStarter(Shooter::createArmShooter, true));

	// Strap operations
	shotTruss->WhenPressed(new ReadyShot(TRUSS_SHOT_POWER,TRUSS_SHOT_ANGLE,3));//100));
	shotNear->WhenPressed(new ReadyShot(NEAR_SHOT_POWER, NEAR_SHOT_ANGLE));
	shotSteep->WhenPressed(new ReadyShot(STEEP_SHOT_POWER, STEEP_SHOT_ANGLE));
	
#if COMPETITION_BOT
	power1->WhenPressed(new ReadyShot(SHOOTER_POWER_TURNS_1));
#else
	power1->WhenPressed(new ReadyShot(SHOOTER_POWER_TURNS_1));
#endif

	// Jaw Override
	jawToggle->WhenPressed(new JawMove(Collector::kClosed));
	jawToggle->WhenReleased(new JawMove(Collector::kOpen));

	resetShooter->WhenPressed(new ResetShooter());
}

Joystick *OI::getJoystickLeft() {
	return joystickLeft;
}

Joystick *OI::getJoystickRight() {
	return joystickRight;
}

bool OI::isShooterArmingPrevented() {
	return !preventShooterArming->Get();
}

float OI::getAngleAdjustment() {
	float volts = DriverStation::GetInstance()->GetEnhancedIO().GetAnalogIn(3);
	return !manAngleOvr->Get() ? 0.56 - (0.3923 * log(4.0 - volts) + 0.3979)
			: 0.0;
}

float OI::getPowerAdjustment() {
	float volts = DriverStation::GetInstance()->GetEnhancedIO().GetAnalogIn(1);
	return !manPowerOvr->Get() ? 0.56 - (0.3923 * log(4.0 - volts) + 0.3979)
			: 0.0;
}

Command * OI::createAngle() {
	return new AngelChange(SmartDashboard::GetNumber("targetangle"));
}
Command * OI::createPower() {
	return new ReadyShot(SmartDashboard::GetNumber("targetpower"));
}
