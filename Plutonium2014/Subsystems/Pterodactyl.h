#ifndef __PTERODACTYL_H
#define __PTERODACTYL_H
#include "Commands/Subsystem.h"
#include "WPILib.h"
#include "../Robotmap.h"

/**
 *
 *
 * @author Dayveed
 */

class AnalogPot;
class DualLiveSpeed;
class PID1983Controller;
class Pterodactyl: public Subsystem, public PIDOutput, public PIDSource {
public:
	enum BrakeState {
		kActive = true, kDeactive = false
	};

private:
	float initialError;
	float target;
	DualLiveSpeed *angleMotors;
	PID1983Controller *pid;
	AnalogPot *pot;
	Relay *brake;
public:
	float angleThreshold;
	Pterodactyl();
	void InitDefaultCommand();

	double getAngle();
	double getRate();
	void setAngleMotorSpeed(float speed);
	float getAngleMotorSpeed();

	int getLimNeg();
	int getLimPos();

	BrakeState getBrake();
	void setBrakeState(BrakeState state);

	void setTarget(float target);
	double getTarget();
	void setOutputRange();
	void stopPID();
	void setTolerance(float tolerance = PTERODACTYL_ANGLE_THRESHOLD);
	bool isPIDFinished(bool ignorePID = false);

	float getPIDTarget();
	virtual void PIDWrite(float f);
	virtual double PIDGet();
	void writeAngleMotorRaw(float f);
};

#endif
