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
class Collector: public Subsystem { // TODO: Make the Jaw state enum make sense
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
	void setPIDEnabled(bool state); 
	double getDiff();
	
	double getRollerSpeed();
	double getRollerDistance();
	
	bool isBallDetected();
};

#endif
