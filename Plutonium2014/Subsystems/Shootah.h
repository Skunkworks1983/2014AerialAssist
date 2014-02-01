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
	AnalogChannel *catPot;
	Encoder *wenchEncoder;
	
	SolenoidPair *latch;
	SolenoidPair *brake;
	
	DigitalInput *pullBackSwitch;
	DigitalInput *latchSensor;
	
public:
	Shootah();
	void InitDefaultCommand();
	void setWenchMotor(float speed);	
	void setLatch(bool state);
	bool getLatch();
	bool isDrawnBack();
	float getWenchPot();
	void engageGearbox(bool isEngaged);
	bool isGearboxEngaged();
	double getWenchEncoder();
	bool isReallyDrawnBack();
};

#endif
