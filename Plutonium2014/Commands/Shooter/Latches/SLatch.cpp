#include "SLatch.h"

// Utils
#include "../../../Utils/Time.h"
#include "../../../Utils/Logger.h"

// Backend
#include "../../../Robotmap.h"

SLatch::SLatch(Shooter::LatchPosition isLocked) :
	CommandBase(CommandBase::createNameFromString("SLatch", isLocked ? "Locked"
			: "Unlocked")) {
	Requires(shooter);
	this->isLocked = isLocked;
	time = 0;
	bTime = 0;
}

void SLatch::Initialize() {
	if (isLocked == Shooter::kUnlatched) {
		Logger::log(Logger::kInfo, "Shooter",
				"Unlatched [Angle: %f (%f +/- %f),\tPower: %f(%f),\tDelay: %f]",
				pterodactyl->getAngle(), pterodactyl->getTarget(),pterodactyl->angleThreshold,
				shooter->getTurns(), shooter->lastReleasePosition, shooter->shootDelay);
	}
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
		Logger::log(Logger::kDiagnostic, "Shooter-SLatch",
				"Time termination; sensor not seen");
		return true;
	}
	return false;
}

void SLatch::End() {

}

void SLatch::Interrupted() {
}
