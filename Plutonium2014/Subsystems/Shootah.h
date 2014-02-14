#ifndef __SHOOTAH_H
#define __SHOOTAH_H
#include "Commands/Subsystem.h"

/**
 *
 *
 * @author David
 */
class SpeedController;
class SolenoidPair;
class DigitalInput;
class AnalogChannel;

class Shootah: public Subsystem {
public:
	enum ShifterPosition {
		kActive,
		kInactive
	};
	
private:
	SpeedController *wenchMotor;
	AnalogChannel *wenchPot;
	
	SolenoidPair *wLatch;
	SolenoidPair *sLatch;
	SolenoidPair *brake;
	
	DigitalInput *pullBackSwitchLeft;
	DigitalInput *pullBackSwitchRight;
	DigitalInput *wLatchSensor;
	DigitalInput *sLatchSensor;
	
	//bool preparedness;
	
public:
	Shootah();
	void InitDefaultCommand();
	void setWenchMotor(float speed);	
	
	void setWLatch(bool state);
	bool getWLatch();
	void setSLatch(bool state);
	bool getSLatch();
	
	double getTurns();
	bool isReallyDrawnBack();
	bool isAngle(float setpoint);
	bool getPullBackSwitch();
	
	double getPotVoltage();

	float getWenchMotorSpeed();
	/*void setPrepared(bool state);
	bool isPrepared();*/
};

#endif
