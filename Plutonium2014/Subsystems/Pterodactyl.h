#ifndef __PTERODACTYL_H
#define __PTERODACTYL_H
#include "Commands/Subsystem.h"
#include "WPILib.h"

/**
 *
 *
 * @author Dayveed
 */

class AnalogPot;
class DualLiveSpeed;
class Pterodactyl: public Subsystem, public PIDOutput {
public:
	enum BrakeState {
		kActive = true, kDeactive = false
	};

private:
	float realSetpoint;
	DualLiveSpeed *angleMotors;
	PIDController *pid;
	AnalogPot *pot;
	Relay *brake;
public:
	Pterodactyl();
	void InitDefaultCommand();

	double getAngle();
	double getRate();
	void setAngle(float target);
	void setAngleMotorSpeed(float speed);
	float getAngleMotorSpeed();

	int getLimNeg();
	int getLimPos();

	BrakeState getBrake();
	void setBrakeState(BrakeState state);

	void setTarget(float target);
	void setOutputRange();
	void stopPID();
	bool isPIDFinished();
	virtual void PIDWrite(float f);
};

#endif
