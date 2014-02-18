#include "WLatch.h"
#include "../../../Utils/Time.h"
#include "../../../Robotmap.h"

WLatch::WLatch(Shootah::LatchPosition state) :
	CommandBase(CommandBase::createNameFromString("WLatch", state
			== Shootah::kLatched ? "Latched" : "Unlatched")) {
	Requires(shootah);
	this->state = state;
	time = 0;
}

void WLatch::Initialize() {
	shootah->setWLatch(state);
	bTime = getCurrentMillis();
}

void WLatch::Execute() {
	time = getCurrentMillis() - bTime;
	if (time > SHOOTAH_WLATCH_WAIT - SHOOTAH_WLATCH_UNLOCK) {
		if (state == Shootah::kUnlatched) {
			shootah->setWenchMotor(SHOOTAH_WENCH_MOTOR_FORCE_UNLATCH);
		} /*else {
			shootah->setWenchMotor(-SHOOTAH_WENCH_MOTOR_FORCE_UNLATCH);
		}*/
	}
}

bool WLatch::IsFinished() {
	if (time >= SHOOTAH_WLATCH_WAIT) {
		return true;
	}
	return false;
}

void WLatch::End() {
	shootah->setWenchMotor(0);
}

void WLatch::Interrupted() {
	shootah->setWenchMotor(0);
}
