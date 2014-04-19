#ifndef __SHOOTER_H
#define __SHOOTER_H
#include "Commands/Subsystem.h"
#include "../Robotmap.h"

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
class Command;

class Shooter : public Subsystem {
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
		int lastRequestedState;
	} DigitalEdgeWatcher;

	StallableMotor *wenchMotor;
	AnalogPot *wenchPot;

	SolenoidPair *wLatch;
	SolenoidPair *sLatch;

#if SHOOTER_LIMITSWITCH
	DigitalInput *pullBackSwitchLeft;
	DigitalInput *pullBackSwitchRight;
	DigitalEdgeWatcher pullBackSwitchPatternBuffer;
#endif

	DigitalInput *sLatchSensor;
	DigitalInput *wLatchSensor;

	DigitalEdgeWatcher sLatchPatternBuffer;

public:
	double lastReleasePosition;
	double shootDelay;
	
	Shooter();
	void InitDefaultCommand();

	static Command *createArmShooter();
	static Command *createCreateArmShooter();

	void setWenchMotor(float speed);
	float getWenchMotorSpeed();

	void setWLatch(LatchPosition state);
	LatchPosition getWLatch();
	void setSLatch(LatchPosition state);
	LatchPosition getRawSLatch();
	bool isLatchedByPattern();
	bool isShooterMotorStalled();

	double getTurns();
	double getTurnRate();

	bool isReallyDrawnBack();

#if SHOOTER_LIMITSWITCH
	bool isLatchedByProximity();
	bool getRawProximity();
#endif

	void checkDiagnostics();
	
	void resetShooter();
};

#endif
