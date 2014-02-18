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

class Shootah : public Subsystem {
public:
	enum LatchPosition {
		kLatched = true, kUnlatched = false
	};
private:
	typedef struct {
		double lastFallingEdge;
		double lastRisingEdge;
		bool lastState;
		double solenoidChangeTime;
		bool lastRequestedState;
	} DigitalEdgeWatcher;

	StallableMotor *wenchMotor;
	AnalogPot *wenchPot;

	SolenoidPair *wLatch;
	SolenoidPair *sLatch;
	SolenoidPair *brake;

#if SHOOTAH_LIMITSWITCH
	DigitalInput *pullBackSwitchLeft;
	DigitalInput *pullBackSwitchRight;
#endif
	
	DigitalInput *sLatchSensor;

	DigitalEdgeWatcher sLatchPatternBuffer;
public:
	Shootah();
	void InitDefaultCommand();
	void setWenchMotor(float speed);

	void setWLatch(LatchPosition state);
	LatchPosition getWLatch();
	void setSLatch(LatchPosition state);
	LatchPosition getRawSLatch();
	bool isLatchedByPattern();

	double getTurns();
	bool isReallyDrawnBack();
	bool isAngle(float setpoint);
#if SHOOTAH_LIMITSWITCH
	bool getPullBackSwitch();
#endif

	float getWenchMotorSpeed();
};

#endif
