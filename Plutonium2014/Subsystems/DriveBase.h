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
	
	// It's desirable that everything possible under private except
	// for methods that implement subsystem capabilities
public:
	enum DriveGear {
		kLow,
		kHigh
	};

	DriveBase();
	void InitDefaultCommand();
	void setSpeed(double speedLeft, double speedRight);
	void setDriveGear(DriveGear gear);
	DriveGear getDriveGear();
};

#endif
