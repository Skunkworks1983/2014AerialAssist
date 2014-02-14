#include "Shootah.h"
#include "../Robotmap.h"
#include "../Utils/SolenoidPair.h"
#include "WPILib.h"

Shootah::Shootah() :
	Subsystem("Shootah") {
	wenchMotor = new Victor(SHOOTAH_MOTOR_WENCH);
	wenchPot = new AnalogChannel(SHOOTAH_CAT_POT);

	wLatch = new SolenoidPair(SHOOTAH_PNEUMATIC_W_LATCH);
	sLatch = new SolenoidPair(SHOOTAH_PNEUMATIC_S_LATCH);

	pullBackSwitchLeft = new DigitalInput(
			SHOOTAH_LIMITSWITCH_LEFT_PULLBACK_CHECK);
	pullBackSwitchRight = new DigitalInput(
			SHOOTAH_LIMITSWITCH_RIGHT_PULLBACK_CHECK);
	
	sLatchSensor = new DigitalInput(SHOOTAH_S_LATCH_SENSOR);
}

void Shootah::InitDefaultCommand() {

}

bool Shootah::getPullBackSwitch() {
	return pullBackSwitchLeft->Get(); //|| pullBackSwitchRight->Get();
}

double Shootah::getTurns() {
	return SHOOTAH_WENCH_POT_TO_DRAW(wenchPot->GetAverageVoltage());
}

double Shootah::getPotVoltage() {
	return wenchPot->GetAverageVoltage();
}

void Shootah::setWenchMotor(float speed) {
	wenchMotor->Set(speed);
}

void Shootah::setSLatch(Shootah::LatchPosition state) {
	sLatch->Set(state);
}

void Shootah::setWLatch(Shootah::LatchPosition state) {
	wLatch->Set(state);
}

Shootah::LatchPosition Shootah::getSLatch() {
	return (Shootah::LatchPosition) sLatchSensor->Get();
}

Shootah::LatchPosition Shootah::getWLatch() {
	return (Shootah::LatchPosition) wLatch->Get();
}

bool Shootah::isReallyDrawnBack() {
	return (getPullBackSwitch() || (getTurns() <= SHOOTAH_WENCH_POT_BACK))/*) && sLatch->Get())*/;
}

bool Shootah::isAngle(float setpoint) {
	return setpoint == getTurns();
}

float Shootah::getWenchMotorSpeed() {
	return wenchMotor->Get();
}
