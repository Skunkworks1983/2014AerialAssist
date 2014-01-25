#ifndef __PTERODACTYL_H
#define __PTERODACTYL_H
#include "Commands/Subsystem.h"
#include "WPILib.h"

/**
 *
 *
 * @author Dayveed
 */
class Pterodactyl: public Subsystem {
private:
	SpeedController *motorLeft;
	SpeedController *motorRight;
	Encoder *encoderLeft;
	Encoder *encoderRight;
	PIDController *pid;
	AnalogChannel *pot;

public:
	Pterodactyl();
	void InitDefaultCommand();
	double getAngle();
	void setAngleMotorSpeed(float speed);
	void setAngle(float target);
};

#endif
