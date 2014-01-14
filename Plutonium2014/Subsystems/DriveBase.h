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
	Encoder *encoderLeftFront;
	Encoder *encoderRightFront;
	Encoder *encoderLeftBack;
	Encoder *encoderRightBack;
	SolenoidPair *shifter;
	
	enum DriveGear {
		kLow,
		kHigh
	};
	
	// It's desirable that everything possible under private except
	// for methods that implement subsystem capabilities
public:
	DriveBase();
	void InitDefaultCommand();
	void setSpeed(double speedLeft, double speedRight);
	void setDriveGear(DriveGear gear);
	DriveGear getDriveGear();
};

#endif
