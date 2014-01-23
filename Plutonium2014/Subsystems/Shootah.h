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
		kBack,
		kAdjusting,
		kAdjusted,
		kUnaligned
	}; 
	
private:
	SpeedController *winchMotor;
	Encoder *winchEncoder;
	
	PIDController *winchPID;
	
	Solenoid *pneumaticCoffeeTable;
	Solenoid *pneumaticBloodyBogan;
	
	DigitalInput *pullbackSwitch;
	
	//ShooterPosition cachedPosition;
	
public:
	Shootah();
	void InitDefaultCommand();
	
	void setWinchPID(float setpoint);
	float getWinchPID(); 
	bool isWinchPIDSetpoint();
	void setWinchPIDState(bool state);
	
	double getEncoder();
	
	void setCoffeeTable(bool state);
	bool getCoffeeTable();
	void setBloodyBogan(bool state);
	bool getBloodyBogan();
	
	bool pullbackDone();
	
	ShooterPosition getShootahPosition();
};

#endif
