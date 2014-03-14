#include "WLatch.h"
// Utils
#include "../../../Utils/Time.h"
#include "../../../Utils/Logger.h"

// Backend
#include "../../../Robotmap.h"

WLatch::WLatch(Shooter::LatchPosition state) :
		CommandBase(
				CommandBase::createNameFromString("WLatch",
						state == Shooter::kLatched ? "Latched" : "Unlatched")) {
	Requires(shooter);
	this->state = state;
	time = 0;
	bTime = 0;
}

void WLatch::Initialize() {
	bTime = getCurrentMillis();
	if (shooter->getWLatch() == state) {
		bTime = 0;
	}
	shooter->setWLatch(state);
	printf("Start WLATCH\n");
}

void WLatch::Execute() {
	shooter->setWLatch(state);
	time = getCurrentMillis() - bTime;
	if (state == Shooter::kLatched&& shooter->getWLatch() == state && time
	< SHOOTER_WLATCH_WAIT - SHOOTER_WLATCH_UNLOCK_DRIVE) {
		bTime = getCurrentMillis()
				- (SHOOTER_WLATCH_WAIT - SHOOTER_WLATCH_UNLOCK_DRIVE) + 1;
	}
	if (state == Shooter::kUnlatched
			&& time > (SHOOTER_WLATCH_WAIT - SHOOTER_WLATCH_UNLOCK_DRIVE)) {
		shooter->setWenchMotor(SHOOTER_WENCH_MOTOR_FORCE_UNLATCH);
	}
	if (state == Shooter::kLatched
			&& time > (SHOOTER_WLATCH_WAIT - SHOOTER_WLATCH_LOCK_DRIVE)) {
		shooter->setWenchMotor(SHOOTER_WENCH_MOTOR_FORCE_LATCH);
	}
}

bool WLatch::IsFinished() {
	if (state == Shooter::kUnlatched && shooter->getWLatch() == state) {
		return true;
	}
	if (time >= SHOOTER_WLATCH_WAIT) {
		if (state != shooter->getWLatch()) {
			Logger::log(Logger::kDiagnostic, "Shooter-WPawl",
					"Time termination; sensor not seen");
		}
		return true;
	}
	return false;
}

void WLatch::End() {
	shooter->setWenchMotor(0);
}

void WLatch::Interrupted() {
	shooter->setWenchMotor(0);
}
