#include "Shootah.h"
#include "../Robotmap.h"
#include "../Utils/SolenoidPair.h"
#include "WPILib.h"

Shootah::Shootah() :
	Subsystem("Shootah") {
	wenchMotor = new Victor(SHOOTAH_MOTOR_WENCH);
	wenchPot = new AnalogChannel(SHOOTAH_CAT_POT);
	
	latch = new SolenoidPair(SHOOTAH_PNEUMATIC_LATCH); 
	gearbox = new SolenoidPair(SHOOTAH_PNEUMATIC_GEARBOX);

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
	return latch->Get();
}

bool Shootah::isDrawnBack(){
	return pullBackSwitch->Get();
}

float Shootah::getWenchPot(){
	return wenchPot->GetAverageValue();
}

void Shootah::engageGearbox(bool isEngaged) {
	gearbox->Set(isEngaged);
}

bool Shootah::isGearboxEngaged(){
	return gearbox->Get();
}

double Shootah::getWenchEncoder(){
	return wenchEncoder->GetDistance();
}

bool Shootah::isDistance(float setpoint){
	return setpoint == wenchPot->GetAverageValue();;
}