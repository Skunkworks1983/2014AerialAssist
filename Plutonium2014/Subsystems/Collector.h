#ifndef __COLLECTOR_H
#define __COLLECTOR_H
#include "Commands/Subsystem.h"

class DigitalInput;
class PIDController;
class SpeedController;
class Encoder;
class SolenoidPair;
class StallableMotor;

/**
 *
 *
 * @author Ross Bajocich
 */
class Collector : public Subsystem { // TODO: Make the Jaw state enum make sense (but no)
public:
	enum JawState {
		kOpen=true, kClosed=false
	};
private:
	SolenoidPair *jawController;
	DigitalInput *jawState;
	DigitalInput *ballSensor;
	PIDController *rollerPIDController;
	Encoder *rollerClawEncoder;
	StallableMotor *rollerMotor;
	
public:
	Collector();
	void InitDefaultCommand();
	JawState getJawState();
	void setJawState(JawState state);

	void setRollerSpeed(float speed);
	void setPIDEnabled(bool state);
	double getDiff();

	double getRollerSpeed();
	double getRollerDistance();

	bool isBallDetected();
};

#endif
