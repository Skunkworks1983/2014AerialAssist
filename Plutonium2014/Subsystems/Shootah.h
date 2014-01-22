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
	Solenoid *pneumaticBloodyBogan;
	
	DigitalInput *pullbackSwitch;
	
	ShooterPosition cachedPosition;
	
public:
	Shootah();
	void InitDefaultCommand();
	
	void setWinchMotorSpeed(float speed);
	double getEncoder();
	
	float getWinchPID(); 
	void setWinchPID(bool enable); // TODO: Make this and all other weird PID functions
	
	void setCoffeTable(bool state);
	bool getCoffeTable();
	void setBloodyBogan(bool state);
	bool getBloodyBogan();
	
	bool pullbackDone();
};

#endif
