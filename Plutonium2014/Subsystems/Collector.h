#ifndef __COLLECTOR_H
#define __COLLECTOR_H
#include "Commands/Subsystem.h"
#include "WPILib/PIDOutput.h"

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
class Collector : public Subsystem, public PIDOutput { // TODO: Make the Jaw state enum make sense (but no)
public:
	enum JawState {
		kOpen=false, kClosed=true
	};
private:
	SolenoidPair *jawController;
	DigitalInput *jawState;
	DigitalInput *ballSensor;
	PIDController *rollerPIDController;
	Encoder *rollerClawEncoder;
	SpeedController *rollerMotorLeft;
	SpeedController *rollerMotorRight;

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
	virtual void PIDWrite(float speed);
};

#endif
