#ifndef OI_H
#define OI_H

class Joystick;
class JoystickButton;
class DigitalIOButton;
class CompositeButton;
class Button;
class AnalogRangeIOButton;

class OI {
private:
	Joystick *joystickLeft;
	Joystick *joystickRight;
	Joystick *joystickButtonsThings;

	JoystickButton *shiftButton;
	JoystickButton *rollerOn;
	JoystickButton *rollerOff;
	JoystickButton *RollerRollOn;
	JoystickButton *RollerRollOff;
	JoystickButton *drawBack;
	JoystickButton *prepare;
	JoystickButton *shootGlatGlat;
	JoystickButton *armODeathZero;
	JoystickButton *armODeathThirty;
	JoystickButton *armODeathSixty;
	JoystickButton *armODeathNintey;
	
	DigitalIOButton *catch1;
	DigitalIOButton *catch2;
	DigitalIOButton *collect;
	DigitalIOButton *pass;
	
	DigitalIOButton *angleFloor;
	DigitalIOButton *angleLow;
	DigitalIOButton *angleMed;
	DigitalIOButton *angleHigh;
	DigitalIOButton *angleCarry;
	
	DigitalIOButton *fire;
	DigitalIOButton *revCollector;
	
	Button *jawToggle;
	
	DigitalIOButton *manShootOvr;
	DigitalIOButton *manAngleOvr;
	
	AnalogRangeIOButton *power1;
	AnalogRangeIOButton *power2;
	AnalogRangeIOButton *power3;
	
	float scale;

public:
	OI();
	Joystick *getJoystickLeft();
	Joystick *getJoystickRight();
	void registerButtonListeners();
	float getScale();
};

#endif
