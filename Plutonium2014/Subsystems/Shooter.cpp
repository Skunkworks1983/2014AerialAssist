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
#include "../Utils/Logger.h"

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

	LiveWindow::GetInstance()->AddActuator("Shooter", "Wench Motor", new DualLiveSpeed(wenchMotor));
	LiveWindow::GetInstance()->AddSensor("Shooter", "Wench Potentiometer", wenchPot);

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
	LiveWindow::GetInstance()->AddSensor("Shooter", "Shooter Latch Sensor", sLatchSensor);

	wLatchSensor = new DigitalInput(SHOOTER_W_LATCH_SENSOR);
	LiveWindow::GetInstance()->AddSensor("Shooter", "Winch Latch Sensor", wLatchSensor);

	// Icky Icky.  This code is repeated
	sLatchPatternBuffer.lastState = !sLatchSensor->Get() ? Shooter::kLatched
			: Shooter::kUnlatched;

	pullBackSwitchPatternBuffer.lastRequestedState = !pullBackSwitchLeft->Get()
			|| !pullBackSwitchRight->Get();
	pullBackSwitchPatternBuffer.lastState
			= !pullBackSwitchPatternBuffer.lastRequestedState;
	if (getRawProximity()) {
		pullBackSwitchPatternBuffer.lastRisingEdge = getCurrentMillis();
	}

	lastReleasePosition = 0;

	setSLatch(Shooter::kLatched);
	wenchMotor->Set(0);
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
>			SHOOTER_WENCH_POT_REVERSE_ALLOW) {
		return new ReadyShot(CommandBase::shooter->lastReleasePosition);
	}
#endif
	CommandGroup *group = new CommandGroup("DrawSeq");
	group->AddSequential(new WaitCommand(1.5));
	group->AddSequential(new DrawShooter());
	return group;
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
			//			Logger::log(Logger::kFinest, "Shooter",
			//					"Cleared proximity pattern buffer due to a recent change");
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
		//		Logger::log(Logger::kFinest, "Shooter",
		//				"Cleared proximity pattern buffer internally");
	}
	if (state && pullBackSwitchPatternBuffer.lastRisingEdge<0) {
		pullBackSwitchPatternBuffer.lastRisingEdge = getCurrentMillis();
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
	if (state == Shooter::kUnlatched) {
#if !SHOOTER_FANCY_LETOUT
		lastReleasePosition = 0.0;
#endif
	}

	int sLatchState = state;
	if (sLatchState != sLatchPatternBuffer.lastRequestedState) {
		sLatchPatternBuffer.solenoidChangeTime = getCurrentMillis();
		sLatchPatternBuffer.lastFallingEdge = -1;
		sLatchPatternBuffer.lastRisingEdge = -1;
		sLatchPatternBuffer.lastRequestedState = sLatchState;
		Logger::log(Logger::kFinest, "Shooter",
				"Cleared shooter latch pattern buffer internally");
	}
}

void Shooter::setWLatch(Shooter::LatchPosition state) {
	wLatch->Set(state);
}

Shooter::LatchPosition Shooter::getRawSLatch() {
	Shooter::LatchPosition pos = !sLatchSensor->Get() ? Shooter::kLatched
			: Shooter::kUnlatched;
	if (sLatchPatternBuffer.lastState != pos && getTurns() < 0.25) {
		// Something happened
		Logger::log(Logger::kFinest, "Shooter",
				"Shooter latch changed from %s to %s",
				sLatchPatternBuffer.lastState == Shooter::kLatched ? "Latched"
						: "Unlatched", pos == Shooter::kLatched ? "Latched"
						: "Unlatched");
		if (pos) {
			sLatchPatternBuffer.lastRisingEdge = getCurrentMillis();
		} else {
			sLatchPatternBuffer.lastFallingEdge = getCurrentMillis();
		}
		if (sLatchPatternBuffer.solenoidChangeTime + SHOOTER_PATTERN_KILLZONE
				> getCurrentMillis()) {
			sLatchPatternBuffer.lastFallingEdge = -1;
			sLatchPatternBuffer.lastRisingEdge = -1;
			Logger::log(Logger::kFinest, "Shooter",
					"Cleared shooter latch pattern buffer due to a recent change");
		}
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

float Shooter::getWenchMotorSpeed() {
	return wenchMotor->Get();
}

double Shooter::getTurnRate() {
	return wenchPot->GetRate();
}

void Shooter::resetShooter() {
	Logger::log(Logger::kInfo, "Shooter", "RESET ALL THE THINGS");
	sLatchPatternBuffer.lastFallingEdge = -1;
	sLatchPatternBuffer.lastRisingEdge = -1;
	if (getRawProximity() && pullBackSwitchPatternBuffer.lastRisingEdge<0) {
		pullBackSwitchPatternBuffer.lastRisingEdge = getCurrentMillis();
	}
}

void Shooter::checkDiagnostics() {
	if (pullBackSwitchLeft->Get() == isReallyDrawnBack()) {
		Logger::log(Logger::kDiagnostic, "Shooter",
				"Left proximity switch doesn't match saved state.");
	}
	if (pullBackSwitchRight->Get() == isReallyDrawnBack()) {
		Logger::log(Logger::kDiagnostic, "Shooter",
				"Right proximity switch doesn't match saved state.");
	}
}
