#ifndef __DRIVE_BASE_H
#define __DRIVE_BASE_H
#include "Commands/Subsystem.h"
#include "WPILib.h"

/**
 *
 *
 * @author David
 */
class DriveBase: public Subsystem {
private:
	Jaguar *motor1;
	Jaguar *motor2;
	Jaguar *motor3;
	Jaguar *motor4;
	Encoder *encoder1;
	Encoder *encoder2;
	Encoder *encoder3;
	Encoder *encoder4;
	// It's desirable that everything possible under private except
	// for methods that implement subsystem capabilities
public:
	DriveBase();
	void InitDefaultCommand();
	void straightDrive(double speed);
	void turnDegree(double degree);	
	void setLeft(double speed);
	void setRight(double speed);
};

#endif
