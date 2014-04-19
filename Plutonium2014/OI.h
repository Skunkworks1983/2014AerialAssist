#ifndef OI_H
#define OI_H

class Button;
class Command;
class Joystick;

class OI {
private:
	Joystick *joystickLeft;
	Joystick *joystickRight;

	Button *collectButton;
	Button *shiftButton;

	Button *catch1;
	Button *resetShooter;
	Button *collect;
	Button *pass;

	Button *angleFloor;
	Button *angleLow;
	Button *shotNearTruss;
	Button *shotFeederTruss;
	Button *startConfig;

	Button *fire;
	Button *gulp;

	Button *jawToggle;

	Button *manAngleOvr;
	Button *manPowerOvr;

	Button *shotIRS;
	Button *shotSteep;
	Button *shotNear;

	Button *preventShooterArming;
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
