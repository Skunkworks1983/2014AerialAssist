#ifndef __COLLECTOR_H
#define __COLLECTOR_H
#include "Commands/Subsystem.h"

class PIDController;
class SpeedController;
class Encoder;
/**
 *
 *
 * @author David
 */
class Collector: public Subsystem {
private:
	PIDController *bangBangLeft;
	PIDController *bangBangRight;
	SpeedController *rollerMotorLeft;
	SpeedController *rollerMotorRight;
	SpeedController *mouthMotorLeft;
	SpeedController *mouthMotorRight;
	Encoder *mouthEncoderLeft;
	Encoder *mouthEncoderRight;
	//Position *defaultPos;
public:
	Collector();
	void InitDefaultCommand();
	//void setArmPosition(Position defaultPos = Collector::kHigh);
	void setRollerSpeed(float speed);
	void setMouthSpeed(float speed);
	
	double getMouthPositionLeft();
	double getMouthPositionRight();
	double getMouthEncoderLeft();
	double getMouthEncoderRight();
	
};

#endif
