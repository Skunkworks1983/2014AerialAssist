#ifndef __PTERODACTYL_H
#define __PTERODACTYL_H
#include "Commands/Subsystem.h"
#include "WPILib.h"

/**
 *
 *
 * @author Dayveed
 */

class SolenoidPair;
class Pterodactyl: public Subsystem {
public:
	enum BrakeState {
		kActive,
		kDeactive
	};
	
private:
	SpeedController *motorLeft;
	SpeedController *motorRight;
	
	Encoder *encoderLeft;
	Encoder *encoderRight;
	
	PIDController *pid;
	AnalogChannel *pot;
	
	DigitalInput *limNeg;
	DigitalInput *limPos;
	
	SolenoidPair *brake;

public:
	Pterodactyl();
	void InitDefaultCommand();
	
	double getAngle();
	void setAngleMotorSpeed(float speed);
	float getAngleMotorSpeed();
	void setAngle(float target);
	
	int getLimNeg();
	int getLimPos();
	
	BrakeState getBrake();
	void setBrakeState(BrakeState state);
};

#endif
