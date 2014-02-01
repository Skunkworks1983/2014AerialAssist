#include "Shootah.h"
#include "../Robotmap.h"
#include "../Utils/SolenoidPair.h"
#include "WPILib.h"

Shootah::Shootah() :
	Subsystem("Shootah") {
	wenchMotor = new Victor(SHOOTAH_MOTOR_WENCH);
	catPot = new AnalogChannel(SHOOTAH_CAT_POT);
	wenchEncoder = new Encoder(SHOOTAH_WENCH_ENCODER, false, Encoder::k4X);
	
	latch = new SolenoidPair(SHOOTAH_PNEUMATIC_LATCH); 
	brake = new SolenoidPair(SHOOTAH_PNEUMATIC_GEARBOX);

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
	return catPot->GetAverageValue();
}

void Shootah::engageGearbox(bool isEngaged) {
	brake->Set(isEngaged);
}

bool Shootah::isGearboxEngaged(){
	return brake->Get();
}

double Shootah::getWenchEncoder(){
	return wenchEncoder->GetDistance();
}

bool Shootah::isReallyPuledBack(){
	return (getLatch() && isDrawnBack && (getWenchPot <= SHOOTAH_WENCH_POT_BACK));
}
