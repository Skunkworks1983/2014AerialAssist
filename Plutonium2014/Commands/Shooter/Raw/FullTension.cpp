#include "FullTension.h"

// Utils
#include "../../../Utils/Time.h"
#include "../../../Utils/Logger.h"

// Backend
#include "../../../Robotmap.h"

FullTension::FullTension() {
	Requires(shooter);
	SetInterruptible(false);
}

void FullTension::Initialize() {
}

void FullTension::Execute() {
	if (!shooter->isReallyDrawnBack()) {
		if (shooter->getTurns() < SHOOTER_WENCH_POT_BACK_NEAR) {
			shooter->setWenchMotor(SHOOTER_WENCH_MOTOR_FULL_BACK_NEAR);
		} else {
			shooter->setWenchMotor(SHOOTER_WENCH_MOTOR_FULL_BACK);
		}
	}
}

bool FullTension::IsFinished() {
	bool state = shooter->isReallyDrawnBack();
	if (shooter->isLatchedByPattern()) {
		Logger::log(Logger::kInfo, "Shooter-FullTension", "Pattern stop");
	}
#if SHOOTER_LIMITSWITCH
	if (shooter->isLatchedByProximity()) {
		Logger::log(Logger::kInfo, "Shooter-FullTension", "Proximity stop");
	}
#endif
	if (shooter->getTurns() <= SHOOTER_WENCH_POT_BACK){
		Logger::log(Logger::kInfo, "Shooter-FullTension", "Potentiometer stop");
	}
	return state;
}

void FullTension::End() {
	Logger::log(Logger::kFiner, "Shooter-FullTension", "Ended full tension");
	shooter->setWenchMotor(0);
	shooter->checkDiagnostics();
}

void FullTension::Interrupted() {
	Logger::log(Logger::kFiner, "Shooter-FullTension", "Interrupted full tension");
	shooter->setWenchMotor(0);
}
