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
class AnalogChannel;

class Shootah: public Subsystem {
public:
	/*enum ShooterPosition {
		kBack,
		kAdjusting,
		kAdjusted,
		kUnaligned
	}; */
	
	enum ShifterPosition {
		kActive,
		kInactive
	};
	
private:
	SpeedController *wenchMotor;
	AnalogChannel *wenchPot;
	
	SolenoidPair *latch;
	SolenoidPair *gearbox;
	
	DigitalInput *pullbackSwitch;
	DigitalInput *latchSensor;
	
public:
	Shootah();
	void InitDefaultCommand();
	void setWenchMotor(float setpoint);	
	void setLatch(bool state);
	bool getLatch();
	bool isDrawnBack();
	float getWenchPot();
	void engageGearbox(bool isEngaged);
	bool isGearboxEngaged();
};

#endif
