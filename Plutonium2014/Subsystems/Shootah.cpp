#include "Shootah.h"
#include "../Robotmap.h"
#include "../Utils/SolenoidPair.h"
#include "WPILib.h"

Shootah::Shootah() :
	Subsystem("Shootah") {
	wenchMotor = new Victor(SHOOTAH_MOTOR_WENCH);
	wenchPot = new AnalogChannel(SHOOTAH_CAT_POT);
	
	latch = new SolenoidPair(SHOOTAH_PNEUMATIC_LATCH); 
	brake = new SolenoidPair(SHOOTAH_PNEUMATIC_BRAKE);

	pullBackSwitch = new DigitalInput(SHOOTAH_LIMITSWITCH_PULLBACK_CHECK);
	latchSensor = new DigitalInput(SHOOTAH_LATCH_SENSOR);
}

void Shootah::InitDefaultCommand() {

}

void Shootah::setWenchMotor(float speed) {
	wenchMotor->Set(speed);
}

void Shootah::setLatch(bool state) {
	latch->Set(state);
}

bool Shootah::getLatch() {
	return latchSensor->Get();
}

bool Shootah::isDrawnBack() {
	return pullBackSwitch->Get();
}

float Shootah::getWenchPot(){
	return wenchPot->GetAverageValue();
}

bool Shootah::getBrake() {
	return brake->Get();
}	

bool Shootah::isReallyDrawnBack(){
	return (getLatch() && isDrawnBack() && (getWenchPot() <= SHOOTAH_WENCH_POT_BACK));
}

bool Shootah::isDistance(float setpoint){
	return setpoint == wenchPot->GetAverageValue();;
}
