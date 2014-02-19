#include "SLatch.h"
#include "../../../Utils/Time.h"
#include "../../../Robotmap.h"

SLatch::SLatch(Shooter::LatchPosition isLocked) :
	CommandBase(CommandBase::createNameFromString("SLatch", isLocked ? "Locked"
			: "Unlocked")) {
	Requires(shooter);
	this->isLocked = isLocked;
	time = 0;
}

void SLatch::Initialize() {
	shooter->setSLatch(isLocked);
	bTime = getCurrentMillis();
}

void SLatch::Execute() {
	time = getCurrentMillis() - bTime;
}

bool SLatch::IsFinished() {
	if (shooter->getRawSLatch() == isLocked) {
		return true;
	} else if (time >= SHOOTER_SLATCH_WAIT) {
		// Shutting down the shooter
		return true;
	}

	return false;
}

void SLatch::End() {

}

void SLatch::Interrupted() {
}
