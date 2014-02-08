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

	//brake = new SolenoidPair(SHOOTAH_PNEUMATIC_BRAKE);

	pullBackSwitchLeft = new DigitalInput(
			SHOOTAH_LIMITSWITCH_LEFT_PULLBACK_CHECK);
	pullBackSwitchRight = new DigitalInput(
			SHOOTAH_LIMITSWITCH_RIGHT_PULLBACK_CHECK);

	wLatchSensor = new DigitalInput(SHOOTAH_W_LATCH_SENSOR);
	sLatchSensor = new DigitalInput(SHOOTAH_S_LATCH_SENSOR);
}

void Shootah::InitDefaultCommand() {

}

bool Shootah::getPullBackSwitch() {
	return pullBackSwitchLeft->Get() || pullBackSwitchRight->Get();
}

double Shootah::getTurns() {
	return SHOOTAH_SLOOP * wenchPot->GetAverageVoltage() + SHOOTAH_YCEPT;
}

double Shootah::getPotVoltage() {
	return wenchPot->GetAverageVoltage();
}

void Shootah::setWenchMotor(float speed) {
	wenchMotor->Set(speed);
}

void Shootah::setSLatch(bool state) {
	sLatch->Set(state);
}

void Shootah::setWLatch(bool state) {
	wLatch->Set(state);
}

bool Shootah::getSLatch() {
	return sLatchSensor->Get();
}

bool Shootah::getWLatch() {
	return wLatchSensor->Get();
}

bool Shootah::getBrake() {
	return brake->Get();
}

void Shootah::setBrake(bool state) {
	brake->Set(state);
}

bool Shootah::isReallyDrawnBack() {
	return (getPullBackSwitch() || (getTurns() <= SHOOTAH_WENCH_POT_BACK));
}

bool Shootah::isAngle(float setpoint) {
	return setpoint == getTurns();
}
