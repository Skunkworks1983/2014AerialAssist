#include "Shootah.h"
#include "../Robotmap.h"
#include "../Utils/SolenoidPair.h"
#include "WPILib.h"

Shootah::Shootah() :
	Subsystem("Shootah") {
	wenchMotor = new Victor(SHOOTAH_MOTOR_WINCH);
	wenchPot = new AnalogChannel(SHOOTAH_WENCH_POT);

	latch = new SolenoidPair(SHOOTAH_PNEUMATIC_LATCH);
	gearbox = new SolenoidPair(SHOOTAH_PNEUMATIC_GEARBOX);

	pullbackSwitch = new DigitalInput(SHOOTAH_LIMITSWITCH_PULLBACK_CHECK);
	latchSensor = new DigitalInput(SHOOTAH_LATCH_SENSOR);
}

void Shootah::InitDefaultCommand() {

}

void Shootah::setWenchMotor(float setpoint) {
	
}

void Shootah::setLatch(bool state) {
	latch->Set(state);
}

bool Shootah::getLatch() {
	return latch->Get();
}

bool Shootah::isDrawnBack(){
	
}

float Shootah::getWenchPot(){
	
}

void Shootah::engageGearbox(isEngaged) {
	
}

bool Shootah::isGearboxEngaged(){
	
}
