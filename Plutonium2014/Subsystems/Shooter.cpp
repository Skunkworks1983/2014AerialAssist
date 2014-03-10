#include "Shooter.h"
#include "../Commands/Shooter/ReadyShot.h"
#include "../Robotmap.h"
#include "../Utils/Actuators/SolenoidPair.h"
#include "../Utils/Actuators/StallableMotor.h"
#include "../Utils/Sensors/AnalogPot.h"
#include "../Utils/Commands/CommandStarter.h"
#include "../Utils/Actuators/DualLiveSpeed.h"
#include "../Utils/Time.h"
#include "WPILib.h"

#include "../Commands/Shooter/DrawShooter.h"

#define SHOOTER_FANCY_LETOUT 0 // Disable fancy letout because Ken

Shooter::Shooter() :
	Subsystem("Shooter") {
	wenchPot = new AnalogPot(SHOOTER_CAT_POT);
	wenchPot->setVoltageToAngle(SHOOTER_POT_TO_DRAW_COEFF);
	wenchMotor = new StallableMotor(new Talon(SHOOTER_MOTOR_WENCH),
			SHOOTER_MOTOR_STALL_SPEED, SHOOTER_MOTOR_STALL_TIME, -1);
	wenchMotor->setPotSource(wenchPot);
	wenchMotor->setName("Winch Motor");

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

	wLatchSensor = new DigitalInput(SHOOTER_W_LATCH_SENSOR);
	LiveWindow::GetInstance()->AddSensor("Shooter", "Winch Latch Sensor",
			wLatchSensor);

	setSLatch(Shooter::kLatched);

	// Icky Icky.  This code is repeated
	sLatchPatternBuffer.lastState = !sLatchSensor->Get() ? Shooter::kLatched
			: Shooter::kUnlatched;

	pullBackSwitchPatternBuffer.lastState = Shooter::kUnlatched;
	pullBackSwitchPatternBuffer.lastRequestedState = sLatch->Get();
	if (getRawProximity()) {
		pullBackSwitchPatternBuffer.lastRisingEdge = getCurrentMillis();
	}

	lastReleasePosition = 0.0;
}

Command *Shooter::createCreateArmShooter() {
	return new CommandStarter(Shooter::createArmShooter, true, 1000.0);
}

Command *Shooter::createArmShooter() {
	if (CommandBase::oi != NULL && CommandBase::oi->isShooterArmingPrevented()) {
		return NULL;
	}
#if SHOOTER_FANCY_LETOUT
	if (CommandBase::shooter != NULL
			&& CommandBase::shooter->lastReleasePosition
					> SHOOTER_WENCH_POT_REVERSE_ALLOW) {
		return new ReadyShot(CommandBase::shooter->lastReleasePosition);
	}
#endif
	return new DrawShooter();
}

bool Shooter::isShooterMotorStalled() {
	return wenchMotor->isStalled();
}

void Shooter::InitDefaultCommand() {

}

#if SHOOTER_LIMITSWITCH
bool Shooter::isLatchedByProximity() {
	bool state = getRawProximity();
	return state && pullBackSwitchPatternBuffer.lastRisingEdge >= 0
			&& pullBackSwitchPatternBuffer.lastRisingEdge
					+ SHOOTER_LIMITSWITCH_DELAY < getCurrentMillis();
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
		if (pullBackSwitchPatternBuffer.solenoidChangeTime
				+ SHOOTER_PATTERN_KILLZONE > getCurrentMillis()) {
			pullBackSwitchPatternBuffer.lastFallingEdge = -1;
			pullBackSwitchPatternBuffer.lastRisingEdge = -1;
			if (sLatch->Get() == Shooter::kLatched) {
				pullBackSwitchPatternBuffer.lastState = true;
			} else {
				pullBackSwitchPatternBuffer.lastState = false;
			}
			printf("Cleared prox pattern buffer recentchange\n");
		}
	}
	if (sLatch->Get() != pullBackSwitchPatternBuffer.lastRequestedState) {
		pullBackSwitchPatternBuffer.solenoidChangeTime = getCurrentMillis();
		pullBackSwitchPatternBuffer.lastFallingEdge = -1;
		pullBackSwitchPatternBuffer.lastRisingEdge = -1;
		pullBackSwitchPatternBuffer.lastRequestedState = sLatch->Get();
		if (sLatch->Get() == Shooter::kLatched) {
			pullBackSwitchPatternBuffer.lastState = true;
		} else {
			pullBackSwitchPatternBuffer.lastState = false;
		}
		printf("Cleared prox pattern buffer internal\n");
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
#if !SHOOTER_FANCY_LETOUT
	if (lastReleasePosition == 0.0 && state == Shooter::kUnlatched) {
		return;
	}
#endif
	sLatch->Set(state);
	if (state == Shooter::kUnlatched) {
#if SHOOTER_FANCY_LETOUT
		lastReleasePosition = 0.0;
#endif
	}
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
	return pos && (sLatchPatternBuffer.lastFallingEdge > 0)
			&& (sLatchPatternBuffer.lastRisingEdge > 0)
			&& (sLatchPatternBuffer.lastFallingEdge
					< sLatchPatternBuffer.lastRisingEdge)
			&& sLatchPatternBuffer.lastRisingEdge
					+ SHOOTER_SLATCH_PATTERN_DELAY < getCurrentMillis();
}

Shooter::LatchPosition Shooter::getWLatch() {
	return !wLatchSensor->Get() ? Shooter::kLatched : Shooter::kUnlatched;
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
