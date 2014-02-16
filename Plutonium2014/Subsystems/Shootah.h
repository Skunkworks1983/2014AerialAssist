#ifndef __SHOOTAH_H
#define __SHOOTAH_H
#include "Commands/Subsystem.h"

/**
 *
 *
 * @author David
 */
class SolenoidPair;
class DigitalInput;
class AnalogChannel;
class AnalogPot;
class StallableMotor;

class Shootah: public Subsystem {
public:
	enum LatchPosition {
		kLatched = true, kUnlatched = false
	};

private:
	StallableMotor *wenchMotor;
	AnalogPot *wenchPot;

	SolenoidPair *wLatch;
	SolenoidPair *sLatch;
	SolenoidPair *brake;

	DigitalInput *pullBackSwitchLeft;
	DigitalInput *pullBackSwitchRight;
	DigitalInput *sLatchSensor;

public:
	Shootah();
	void InitDefaultCommand();
	void setWenchMotor(float speed);

	void setWLatch(LatchPosition state);
	LatchPosition getWLatch();
	void setSLatch(LatchPosition state);
	LatchPosition getSLatch();

	double getTurns();
	bool isReallyDrawnBack();
	bool isAngle(float setpoint);
	bool getPullBackSwitch();

	float getWenchMotorSpeed();
};

#endif
