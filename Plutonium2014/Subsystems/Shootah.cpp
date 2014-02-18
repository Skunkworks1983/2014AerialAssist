#include "Shootah.h"
#include "../Robotmap.h"
#include "../Utils/Actuators/SolenoidPair.h"
#include "../Utils/Actuators/StallableMotor.h"
#include "../Utils/Sensors/AnalogPot.h"
#include "../Utils/Actuators/DualLiveSpeed.h"
#include "../Utils/Time.h"
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

#if SHOOTAH_LIMITSWITCH
	pullBackSwitchLeft = new DigitalInput(
			SHOOTAH_LIMITSWITCH_LEFT_PULLBACK_CHECK);
	LiveWindow::GetInstance()->AddSensor("Shootah", "Left Pullback Switch", pullBackSwitchLeft);

	pullBackSwitchRight = new DigitalInput(
			SHOOTAH_LIMITSWITCH_RIGHT_PULLBACK_CHECK);
	LiveWindow::GetInstance()->AddSensor("Shootah", "Right Pullback Switch",
			pullBackSwitchRight);
#endif

	sLatchSensor = new DigitalInput(SHOOTAH_S_LATCH_SENSOR);
	LiveWindow::GetInstance()->AddSensor("Shootah", "Shooter Latch Sensor", sLatchSensor);

	sLatchPatternBuffer.lastState = !sLatchSensor->Get() ? Shootah::kLatched
			: Shootah::kUnlatched;
}

void Shootah::InitDefaultCommand() {

}

#if SHOOTAH_LIMITSWITCH
bool Shootah::getPullBackSwitch() {
	return !pullBackSwitchLeft->Get(); //|| pullBackSwitchRight->Get();
}
#endif

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

Shootah::LatchPosition Shootah::getRawSLatch() {
	Shootah::LatchPosition pos = !sLatchSensor->Get() ? Shootah::kLatched
			: Shootah::kUnlatched;
	if (sLatchPatternBuffer.lastState != pos) {
		// Something happened
		printf("SLatched changed from %d to %d\n",
				sLatchPatternBuffer.lastState, pos);
		if (pos) {
			sLatchPatternBuffer.lastRisingEdge = getCurrentMillis();
		} else {
			sLatchPatternBuffer.lastFallingEdge = getCurrentMillis();
		}
		if (sLatchPatternBuffer.solenoidChangeTime + SHOOTAH_PATTERN_KILLZONE > getCurrentMillis()) {
			sLatchPatternBuffer.lastFallingEdge = -1;
			sLatchPatternBuffer.lastRisingEdge = -1;
			printf("Cleared pattern buffer recentchange\n");
		}
	}
	if (sLatch->Get() != sLatchPatternBuffer.lastRequestedState) {
		sLatchPatternBuffer.solenoidChangeTime = getCurrentMillis();
		sLatchPatternBuffer.lastFallingEdge = -1;
		sLatchPatternBuffer.lastRisingEdge = -1;
		sLatchPatternBuffer.lastRequestedState = sLatch->Get();
		printf("Cleared pattern buffer internal\n");
	}
	sLatchPatternBuffer.lastState = pos;
	return pos;
}

bool Shootah::isLatchedByPattern() {
	Shootah::LatchPosition pos = getRawSLatch();
	return (sLatchPatternBuffer.lastFallingEdge> 0)
			&& (sLatchPatternBuffer.lastRisingEdge> 0)
			&& (sLatchPatternBuffer.lastFallingEdge
					< sLatchPatternBuffer.lastRisingEdge) && pos;
}

Shootah::LatchPosition Shootah::getWLatch() {
	return wLatch->Get() ? Shootah::kLatched : Shootah::kUnlatched;
}

bool Shootah::isReallyDrawnBack() {
#if SHOOTAH_LIMITSWITCH
	return (getPullBackSwitch() || (getTurns() <= SHOOTAH_WENCH_POT_BACK)
			|| isLatchedByPattern());
#else
	return (getTurns() <= SHOOTAH_WENCH_POT_BACK) || isLatchedByPattern();
#endif
}

bool Shootah::isAngle(float setpoint) {
	return setpoint == getTurns();
}

float Shootah::getWenchMotorSpeed() {
	return wenchMotor->Get();
}
