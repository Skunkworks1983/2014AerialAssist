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
	void updatePIDOutput();

public:
	Pterodactyl();
	void InitDefaultCommand();
	double PIDGet();
	void setPIDState(bool bee);
	bool isPIDDone();
	void setPitch(float direction);
	float getPitch();
};

#endif
