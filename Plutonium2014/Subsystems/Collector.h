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
class Collector: public Subsystem { // TODO: Make the Jaw state enum make sense (but no)
private:
	SolenoidPair *jawController;
	DigitalInput *jawState;
	DigitalInput *ballSensor;
	PIDController *rollerPIDControllerLeft;
	PIDController *rollerPIDControllerRight;
	Encoder *rollerClawEncoderLeft;
	Encoder *rollerClawEncoderRight;
	SpeedController *rollerMotorLeft;
	SpeedController *rollerMotorRight;

	
public:
	Collector();
	void InitDefaultCommand();
	bool getJawState();
	void setJawState(bool on);
	
	void setRollerSpeedLeft(float speed);
	void setPIDEnabledLeft(bool state); 
	double getDiffLeft();
	
	double getRollerSpeedLeft();
	double getRollerDistanceLeft();
	
	void setRollerSpeedRight(float speed);
	void setPIDEnabledRight(bool state);
	double getDiffRight();

	double getRollerSpeedRight();
	double getRollerDistanceRight();
	
	bool isBallDetected();
};

#endif
