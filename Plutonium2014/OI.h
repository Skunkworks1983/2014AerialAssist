#ifndef OI_H
#define OI_H

class Joystick;
class JoystickButton;
class DigitalIOButton;
class CompositeButton;
class Button;
class AnalogRangeIOButton;
class Command;

class OI {
private:
	Joystick *joystickLeft;
	Joystick *joystickRight;

	CompositeButton *collectButton;
	JoystickButton *shiftButton;

	DigitalIOButton *catch1;
	DigitalIOButton *resetShooter;
	DigitalIOButton *collect;
	DigitalIOButton *pass;

	DigitalIOButton *angleFloor;
	DigitalIOButton *angleLow;
	DigitalIOButton *angleMed;
	DigitalIOButton *shotTruss;
	DigitalIOButton *startConfig;

	DigitalIOButton *fire;
	DigitalIOButton *revCollector;

	Button *jawToggle;

	DigitalIOButton *manAngleOvr;
	DigitalIOButton *manPowerOvr;

	AnalogRangeIOButton *power1;
	AnalogRangeIOButton *power2;
	AnalogRangeIOButton *shotNear;

	DigitalIOButton *preventShooterArming;
public:
	OI();
	Joystick *getJoystickLeft();
	Joystick *getJoystickRight();
	bool isShooterArmingPrevented();
	void registerButtonListeners();

	float getAngleAdjustment();
	float getPowerAdjustment();
	
	static Command *createPower();
	static Command *createAngle();
};

#endif
