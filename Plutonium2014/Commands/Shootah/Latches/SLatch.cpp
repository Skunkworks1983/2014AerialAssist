#include "SLatch.h"
#include "../../../Utils/Time.h"
#include "../../../Robotmap.h"

SLatch::SLatch(Shootah::LatchPosition isLocked) :
	CommandBase(CommandBase::createNameFromString("SLatch", isLocked ? "Locked"
			: "Unlocked")) {
	Requires(shootah);
	this->isLocked = isLocked;
	time = 0;
}

void SLatch::Initialize() {
	shootah->setSLatch(isLocked);
	bTime = getCurrentMillis();
}

void SLatch::Execute() {
	time = getCurrentMillis() - bTime;
}

bool SLatch::IsFinished() {
	if (shootah->getRawSLatch() == isLocked) {
		return true;
	} else if (time >= SHOOTAH_SLATCH_WAIT) {
		// Shutting down the shooter
		return true;
	}

	return false;
}

void SLatch::End() {

}

void SLatch::Interrupted() {
}
