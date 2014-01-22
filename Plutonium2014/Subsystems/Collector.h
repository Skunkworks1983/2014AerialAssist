#ifndef __COLLECTOR_H
#define __COLLECTOR_H
#include "Commands/Subsystem.h"

class DigitalInput;
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
	PIDController *rollerClawController;
	SpeedController *rollerMotorLeft;
	SpeedController *rollerClawMotor;
	SpeedController *mouthMotorLeft;
	SpeedController *mouthMotorRight;
	Encoder *mouthEncoderLeft;
	Encoder *rollerClawEncoder;
	DigitalInput *ballSensor;
	
	//Position *defaultPos;
public:
	Collector();
	void InitDefaultCommand();
	//void setArmPosition(Position defaultPos = Collector::kHigh);
	void setRollerSpeed(float speed);
	void setMouthSpeed(float speed);
	
	double getMouthPositionLeft();
	double getRollerClaw();
	double getMouthEncoderLeft();
	double getMouthEncoderRight();
	
};

#endif
