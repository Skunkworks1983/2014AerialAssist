#ifndef __SHOOTAH_H
#define __SHOOTAH_H
#include "Commands/Subsystem.h"

/**
 *
 *
 * @author David
 */
class SpeedController;
class Encoder;
class Solenoid;
class DigitalInput;
class PIDController;

class Shootah: public Subsystem {
public:
	enum ShooterPosition {
		kPrepped,
		kAdjusting,
		kUnaligned
	}; 
private:
	SpeedController *winchMotor;
	Encoder *winchEncoder;
	
	PIDController *winchPID;
	
	Solenoid *pneumaticCoffeeTable;
	Solenoid *pneumaticWanker;
	
	DigitalInput *pullbackSwitch;
	
	ShooterPosition cachedPosition;
	
public:
	Shootah();
	void InitDefaultCommand();
	
	void setWinchMotorSpeed(float speed);
	double getEncoder();
	
	float getWinchPID(); 
	void setWinchPID(); // TODO: Make this and all other weird PID functions
	
	void setCoffeTable(bool state);
	bool getCoffeTable();
	void setWanker(bool state);
	bool getWanker();
	
	bool pullbackDone();
};

#endif
