#include "Shootah.h"
#include "../Robotmap.h"
#include "../Utils/SolenoidPair.h"
#include "../Utils/StallableMotor.h"
#include "../Utils/AnalogPot.h"
#include "../Utils/DualLiveSpeed.h"
#include "WPILib.h"

Shootah::Shootah() :
	Subsystem("Shootah") {
	wenchPot = new AnalogPot(SHOOTAH_CAT_POT);
	wenchPot->setVoltageToAngle(SHOOTAH_POT_TO_DRAW_COEFF);
	wenchMotor = new StallableMotor(new Talon(SHOOTAH_MOTOR_WENCH), -1.0);
	wenchMotor->setPotSource(wenchPot);
	//wenchMotor = new Victor(SHOOTAH_MOTOR_WENCH);
	LiveWindow::GetInstance()->AddActuator("Shootah", "Wench Motor", new DualLiveSpeed(wenchMotor));
	LiveWindow::GetInstance()->AddSensor("Shootah", "Wench Potentiometer", wenchPot);

	wLatch = new SolenoidPair(SHOOTAH_PNEUMATIC_W_LATCH);
	LiveWindow::GetInstance()->AddActuator("Shootah", "Wench Latch", wLatch);
	sLatch = new SolenoidPair(SHOOTAH_PNEUMATIC_S_LATCH);
	LiveWindow::GetInstance()->AddActuator("Shootah", "Shooter Latch", sLatch);

	pullBackSwitchLeft = new DigitalInput(
			SHOOTAH_LIMITSWITCH_LEFT_PULLBACK_CHECK);
	LiveWindow::GetInstance()->AddSensor("Shootah", "Left Pullback Switch", pullBackSwitchLeft);

	pullBackSwitchRight = new DigitalInput(
			SHOOTAH_LIMITSWITCH_RIGHT_PULLBACK_CHECK);
	LiveWindow::GetInstance()->AddSensor("Shootah", "Right Pullback Switch",
			pullBackSwitchRight);

	sLatchSensor = new DigitalInput(SHOOTAH_S_LATCH_SENSOR);
	LiveWindow::GetInstance()->AddSensor("Shootah", "Shooter Latch Sensor", sLatchSensor);
}

void Shootah::InitDefaultCommand() {

}

bool Shootah::getPullBackSwitch() {
	return !pullBackSwitchLeft->Get(); //|| pullBackSwitchRight->Get();
}

double Shootah::getTurns() {
	return wenchPot->GetAngle();
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
	return sLatchSensor->Get() ? Shootah::kLatched : Shootah::kUnlatched;
}

Shootah::LatchPosition Shootah::getWLatch() {
	return wLatch->Get() ? Shootah::kLatched : Shootah::kUnlatched;
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
