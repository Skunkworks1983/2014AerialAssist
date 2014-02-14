#ifndef __DRIVE_BASE_H
#define __DRIVE_BASE_H

class SpeedController;
class Encoder;
class SolenoidPair;

#include "WPILib.h"
/**
 *
 *
 * @author David
 */
class DriveBase: public Subsystem {
private:
	SpeedController *motorLeftFront;
	SpeedController *motorRightFront;
	SpeedController *motorLeftBack;
	SpeedController *motorRightBack;
	Encoder *encoderLeft;
	Encoder *encoderRight;
	Encoder *encoderLeftBack;
	Encoder *encoderRightBack;
	SolenoidPair *shifter;
	Gyro *gyro;
	// It's desirable that everything possible under private except
	// for methods that implement subsystem capabilities

public:
	enum DriveGear {
		kLow = false, kHigh = true
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
	Gyro *getGyro();
};

#endif
