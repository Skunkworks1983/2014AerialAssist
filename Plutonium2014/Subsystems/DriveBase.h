#ifndef __DRIVE_BASE_H
#define __DRIVE_BASE_H

class SpeedController;
class Encoder;
class SolenoidPair;
class DualLiveSpeed;

#include "WPILib.h"
/**
 *
 *
 * @author David
 */
class DriveBase: public Subsystem {
private:
	DualLiveSpeed *motorLeft;
	DualLiveSpeed *motorRight;
	Encoder *encoderLeft;
	Encoder *encoderRight;
	SolenoidPair *shifter;
public:
	enum DriveGear {
		kLow = true, kHigh = false
	};

	DriveBase();
	void InitDefaultCommand();
	void setSpeed(double speedLeft, double speedRight);
	Encoder *getLeftEncoder();
	Encoder *getRightEncoder();
	void encoderReset();
	void setDriveGear(DriveGear gear);
	DriveGear getDriveGear();
	float getMotorSpeed();
};

#endif
