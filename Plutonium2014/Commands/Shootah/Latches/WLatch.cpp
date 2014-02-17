#include "WLatch.h"
#include "../../../Utils/Time.h"
#include "../../../Robotmap.h"

WLatch::WLatch(Shootah::LatchPosition state) :
	CommandBase(CommandBase::createNameFromString("WLatch", state
			== Shootah::kLatched ? "Latched" : "Unlatched")) {
	Requires(shootah);
	this->state = state;
	time = 0;
	bTime = getCurrentMillis();
}

void WLatch::Initialize() {
	shootah->setWLatch(state);
}

void WLatch::Execute() {
	time = getCurrentMillis() - bTime;
	if (time > SHOOTAH_WLATCH_WAIT - SHOOTAH_WLATCH_UNLOCK) {
		shootah->setWenchMotor(-0.25);
	}
}

bool WLatch::IsFinished() {
	if (shootah->getWLatch() == state) {
		return true;
	} else if (time >= SHOOTAH_WLATCH_WAIT) {
		printf("error stuff\n");
		// error stuff aka dankSuperdawg
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
