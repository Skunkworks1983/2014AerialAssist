#include "Shooter.h"
#include "../Robotmap.h"
#include "../Utils/Actuators/SolenoidPair.h"
#include "../Utils/Actuators/StallableMotor.h"
#include "../Utils/Sensors/AnalogPot.h"
#include "../Utils/Actuators/DualLiveSpeed.h"
#include "../Utils/Time.h"
#include "WPILib.h"

#include "../Commands/Shooter/DrawShooter.h"

Shooter::Shooter() :
	Subsystem("Shooter") {
	wenchPot = new AnalogPot(SHOOTER_CAT_POT);
	wenchPot->setVoltageToAngle(SHOOTER_POT_TO_DRAW_COEFF);
	wenchMotor = new StallableMotor(new Talon(SHOOTER_MOTOR_WENCH), -1.0);
	wenchMotor->setPotSource(wenchPot);
	//wenchMotor = new Victor(SHOOTER_MOTOR_WENCH);
	LiveWindow::GetInstance()->AddActuator("Shooter", "Wench Motor",
			new DualLiveSpeed(wenchMotor));
	LiveWindow::GetInstance()->AddSensor("Shooter", "Wench Potentiometer",
			wenchPot);

	wLatch = new SolenoidPair(SHOOTER_PNEUMATIC_W_LATCH);
	LiveWindow::GetInstance()->AddActuator("Shooter", "Wench Latch", wLatch);
	sLatch = new SolenoidPair(SHOOTER_PNEUMATIC_S_LATCH);
	LiveWindow::GetInstance()->AddActuator("Shooter", "Shooter Latch", sLatch);

#if SHOOTER_LIMITSWITCH
	pullBackSwitchLeft = new DigitalInput(
			SHOOTER_LIMITSWITCH_LEFT_PULLBACK_CHECK);

	pullBackSwitchRight = new DigitalInput(
			SHOOTER_LIMITSWITCH_RIGHT_PULLBACK_CHECK);
#endif

	sLatchSensor = new DigitalInput(SHOOTER_S_LATCH_SENSOR);
	LiveWindow::GetInstance()->AddSensor("Shooter", "Shooter Latch Sensor",
			sLatchSensor);

	sLatchPatternBuffer.lastState = !sLatchSensor->Get() ? Shooter::kLatched
			: Shooter::kUnlatched;
}

Command *Shooter::createArmShooter() {
	return new DrawShooter();
}

void Shooter::InitDefaultCommand() {

}

#if SHOOTER_LIMITSWITCH
bool Shooter::isLatchedByProximity() {
	bool state = getRawProximity();
	return state && pullBackSwitchPatternBuffer.lastRisingEdge + SHOOTER_LIMITSWITCH_DELAY < getCurrentMillis();
}
bool Shooter::getRawProximity() {
	bool state = !pullBackSwitchLeft->Get() || !pullBackSwitchRight->Get();
	if (pullBackSwitchPatternBuffer.lastState != state) {
		pullBackSwitchPatternBuffer.lastState = state;
		if (state) {
			pullBackSwitchPatternBuffer.lastRisingEdge = getCurrentMillis();
		} else {
			pullBackSwitchPatternBuffer.lastFallingEdge = getCurrentMillis();
		}
	}
	return state;
}
#endif

double Shooter::getTurns() {
	return wenchPot->GetAngle();
}

void Shooter::setWenchMotor(float speed) {
	wenchMotor->Set(speed);
}

void Shooter::setSLatch(Shooter::LatchPosition state) {
	sLatch->Set(state);
}

void Shooter::setWLatch(Shooter::LatchPosition state) {
	wLatch->Set(state);
}

Shooter::LatchPosition Shooter::getRawSLatch() {
	Shooter::LatchPosition pos = !sLatchSensor->Get() ? Shooter::kLatched
			: Shooter::kUnlatched;
	if (sLatchPatternBuffer.lastState != pos) {
		// Something happened
		printf("SLatched changed from %d to %d\n",
				sLatchPatternBuffer.lastState, pos);
		if (pos) {
			sLatchPatternBuffer.lastRisingEdge = getCurrentMillis();
		} else {
			sLatchPatternBuffer.lastFallingEdge = getCurrentMillis();
		}
		if (sLatchPatternBuffer.solenoidChangeTime + SHOOTER_PATTERN_KILLZONE
				> getCurrentMillis()) {
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

bool Shooter::isLatchedByPattern() {
	Shooter::LatchPosition pos = getRawSLatch();
	return (sLatchPatternBuffer.lastFallingEdge > 0)
			&& (sLatchPatternBuffer.lastRisingEdge > 0)
			&& (sLatchPatternBuffer.lastFallingEdge
					< sLatchPatternBuffer.lastRisingEdge) && pos;
}

Shooter::LatchPosition Shooter::getWLatch() {
	return wLatch->Get() ? Shooter::kLatched : Shooter::kUnlatched;
}

bool Shooter::isReallyDrawnBack() {
#if SHOOTER_LIMITSWITCH
	return (isLatchedByProximity() || (getTurns() <= SHOOTER_WENCH_POT_BACK)
			|| isLatchedByPattern());
#else
	return (getTurns() <= SHOOTER_WENCH_POT_BACK) || isLatchedByPattern();
#endif
}

bool Shooter::isAngle(float setpoint) {
	return setpoint == getTurns();
}

float Shooter::getWenchMotorSpeed() {
	return wenchMotor->Get();
}

double Shooter::getTurnRate() {
	return wenchPot->GetRate();
}
