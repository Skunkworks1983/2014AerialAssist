#ifndef __COLLECTOR_H
#define __COLLECTOR_H
#include "Commands/Subsystem.h"

class DigitalInput;
class PIDController;
class SpeedController;
class Encoder;
class SolenoidPair;
/**
 *
 *
 * @author Ross Bajocich
 */
class Collector: public Subsystem {
private:
	SolenoidPair *jawController;
	DigitalInput *jawState;
	DigitalInput *ballSensor;
	PIDController *rollerPIDController;
	Encoder *rollerClawEncoder;
	SpeedController *rollerMotor;
	
public:
	Collector();
	void InitDefaultCommand();
	bool getJawState();
	void setJawState(bool on);
	
	void setRollerSpeed(float speed);
	double getRollerSpeed();
	double getRollerDistance();
	
	bool isBallDetected();
};

#endif
