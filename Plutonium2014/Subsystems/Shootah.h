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
class SolenoidPair;
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
	
	enum ShifterPosition {
		kActive,
		kInactive
	};
	
private:
	SpeedController *winchMotor;
	Encoder *winchEncoder;
	
	PIDController *winchPID;
	
	SolenoidPair *pneumaticCoffeeTable;
	SolenoidPair *pneumaticBloodyBogan;
	
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
	void setBloodyBogan(ShifterPosition state);
	ShifterPosition getBloodyBogan();
	
	bool pullbackDone();
	
	ShooterPosition getShootahPosition();
};

#endif
