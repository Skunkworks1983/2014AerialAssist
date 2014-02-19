#include "WLatch.h"
#include "../../../Utils/Time.h"
#include "../../../Robotmap.h"

WLatch::WLatch(Shooter::LatchPosition state) :
	CommandBase(CommandBase::createNameFromString("WLatch", state
			== Shooter::kLatched ? "Latched" : "Unlatched")) {
	Requires(shooter);
	this->state = state;
	time = 0;
}

void WLatch::Initialize() {
	bTime = getCurrentMillis();
	if (shooter->getWLatch() == state) {
		bTime = 0;
	}
	shooter->setWLatch(state);
}

void WLatch::Execute() {
	time = getCurrentMillis() - bTime;
	if (state == Shooter::kUnlatched && time
			> (SHOOTER_WLATCH_WAIT - SHOOTER_WLATCH_UNLOCK_DRIVE)) {
		shooter->setWenchMotor(SHOOTER_WENCH_MOTOR_FORCE_UNLATCH);
	}
	if (state == Shooter::kLatched && time
			> (SHOOTER_WLATCH_WAIT - SHOOTER_WLATCH_LOCK_DRIVE)) {
		shooter->setWenchMotor(SHOOTER_WENCH_MOTOR_FORCE_LATCH);
	}
}

bool WLatch::IsFinished() {
	if (time >= SHOOTER_WLATCH_WAIT) {
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
