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
#define SAFE_BUTTON(name, cmd) {if (name!=NULL){cmd;}}

OI::OI() {
#if PRACTICE_OI

	joystickLeft = new Joystick(OI_JOYSTICK_LEFT);
	joystickRight = new Joystick(OI_JOYSTICK_RIGHT);
	shiftButton = new JoystickButton(joystickLeft, 1);
	collectButton = new CompositeButton(new JoystickButton(joystickRight, 1),NULL,CompositeButton::kNOT);

	catch1 = NULL;
	resetShooter = new DigitalIOButton(8);
	collect = NULL;
	shotIRS = NULL;//new DigitalIOButton(13);

	angleFloor = new DigitalIOButton(1);
	angleLow = NULL;
	shotNearTruss = new DigitalIOButton(13);
	shotFeederTruss = new DigitalIOButton(11);
	startConfig = new DigitalIOButton(16);

	fire = new DigitalIOButton(5);
	gulp = new DigitalIOButton(10);
	manAngleOvr = NULL;
	manPowerOvr = NULL;
	pass = NULL;
	shotSteep = NULL;
	preventShooterArming = NULL;

	jawToggle = new DigitalIOButton(15);
	shotNear = new DigitalIOButton(3);
#else
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
	shotNearTruss = new DigitalIOButton(8);
	shotFeederTruss = new DigitalIOButton(13);
	startConfig = new DigitalIOButton(15);

	fire = new DigitalIOButton(2);
	gulp = new DigitalIOButton(9);
	jawToggle = new OverridableButton(new DigitalIOButton(12),
			new DigitalIOButton(11), false);
	preventShooterArming = new DigitalIOButton(10);
	manAngleOvr = new DigitalIOButton(16);
	manPowerOvr = new DigitalIOButton(14);

	shotNear = new AnalogRangeIOButton(OI_SHOOTER_POWER_PORT,
			1.115 - OI_ANALOG_TRESHOLD, 1.115 + OI_ANALOG_TRESHOLD);
	shotSteep = new AnalogRangeIOButton(OI_SHOOTER_POWER_PORT,
			1.677 - OI_ANALOG_TRESHOLD, 1.677 + OI_ANALOG_TRESHOLD);
	shotIRS = new AnalogRangeIOButton(OI_SHOOTER_POWER_PORT,
			3.342 - OI_ANALOG_TRESHOLD, 3.342 + OI_ANALOG_TRESHOLD);
#endif
}
void OI::registerButtonListeners() {
	// Drivebase
	SAFE_BUTTON(shiftButton,shiftButton->WhenPressed(new Shift(Shift::kLow)));
	SAFE_BUTTON(shiftButton,shiftButton->WhenReleased(new Shift(Shift::kHigh)));

	// Pterodactyl Angle
	SAFE_BUTTON(angleFloor,angleFloor->WhenPressed(new AngelChange(0)));
	SAFE_BUTTON(angleLow,angleLow->WhenPressed(new AngelChange(30)));

	CommandGroup *startCfgCmd = new CommandGroup();
	startCfgCmd->AddSequential(new AngelChange(111.5));
	startCfgCmd->AddParallel(new JawMove(Collector::kClosed));
	SAFE_BUTTON(startConfig,startConfig->WhenPressed(startCfgCmd));

	// Collector rollers
	SAFE_BUTTON(gulp,gulp->WhenPressed(new Gulp()));
	//new RollerRoll(-COLLECTOR_ROLLER_INTAKE_SET_POINT));
	SAFE_BUTTON(collect,START_STOP_COMMAND(collect, new Collect(), 1));
	SAFE_BUTTON(collectButton,START_STOP_COMMAND(collectButton, new Collect(), 1));

	// Jaw Operations
	SAFE_BUTTON(pass, pass->WhenPressed(new Pass()));
	SAFE_BUTTON(catch1, catch1->WhenPressed(new Catch(90)));

	// Shooter operations
	SAFE_BUTTON(fire,fire->WhenReleased(new FireShooter()));
	//fire->WhenPressed(new CommandStarter(Shooter::createArmShooter, true));

	// Strap operations
	SAFE_BUTTON(shotFeederTruss,shotFeederTruss->WhenPressed(new ReadyShot(FEEDER_TRUSS_SHOT_POWER, FEEDER_TRUSS_SHOT_ANGLE, FEEDER_TRUSS_SHOT_TOLERANCE, FEEDER_TRUSS_SHOT_DELAY)));
	SAFE_BUTTON(shotNearTruss,shotNearTruss->WhenPressed(new ReadyShot(NEAR_TRUSS_SHOT_POWER, NEAR_TRUSS_SHOT_ANGLE, NEAR_TRUSS_SHOT_TOLERANCE, NEAR_TRUSS_SHOT_DELAY)));
	SAFE_BUTTON(shotNear,shotNear->WhenPressed(new ReadyShot(NEAR_SHOT_POWER, NEAR_SHOT_ANGLE)));
	SAFE_BUTTON(shotSteep,shotSteep->WhenPressed(new ReadyShot(STEEP_SHOT_POWER, STEEP_SHOT_ANGLE)));
	SAFE_BUTTON(shotIRS, shotIRS->WhenPressed(new ReadyShot(IRS_SHOT_POWER, IRS_SHOT_ANGLE, IRS_SHOT_TOLERANCE)));

	// Jaw Override
	SAFE_BUTTON(jawToggle,jawToggle->WhenPressed(new JawMove(Collector::kClosed)));
	SAFE_BUTTON(jawToggle,jawToggle->WhenReleased(new JawMove(Collector::kOpen)));

	SAFE_BUTTON(resetShooter,resetShooter->WhenPressed(new ResetShooter()));

	SmartDashboard::PutData("go power target", new CommandStarter(OI::createPower));
	SmartDashboard::PutData("go target", new CommandStarter(OI::createAngle));
}

Joystick *OI::getJoystickLeft() {
	return joystickLeft;
}

Joystick *OI::getJoystickRight() {
	return joystickRight;
}

bool OI::isShooterArmingPrevented() {
	return preventShooterArming != NULL && !preventShooterArming->Get();
}

float OI::getAngleAdjustment() {
	if (manAngleOvr==NULL) {
		return 0;
	}
	float volts = DriverStation::GetInstance()->GetEnhancedIO().GetAnalogIn(3);
	return !manAngleOvr->Get() ? 0.56 - (0.3923 * log(4.0 - volts) + 0.3979)
			: 0.0;
}

float OI::getPowerAdjustment() {
	if (manPowerOvr==NULL) {
		return 0;
	}
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
