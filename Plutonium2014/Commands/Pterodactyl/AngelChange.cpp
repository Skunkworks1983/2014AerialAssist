#include "AngelChange.h"
// CSTDLIB
#include <math.h>

#include "../../Utils/Time.h"

// Backend
#include "../../Robotmap.h"

#define ASYNC_BRAKE 1

AngelChange::AngelChange(float target, float timeout) :
	CommandBase(CommandBase::createNameFromFloat("AngleChange", target)) {
	Requires(pterodactyl);
	this->target = target;
	this->stability = 0;
	this->tmpTarget = 0;
	//SetTimeout(timeout);
	SetInterruptible(true);
}

void AngelChange::Initialize() {
	//	if ((fabs(target - pterodactyl->getAngle())) > PTERODACTYL_ANGLE_THRESHOLD) {
	pterodactyl->setBrakeState(Pterodactyl::kDeactive);
	tmpTarget = target<=0 ? -3 : target;
	if (tmpTarget < 45 && shooter->getTurns() > 0.25 && !shooter->isReallyDrawnBack()) {
		tmpTarget = 45; //Safeties  Collector shouldn't go down in this case
	}
	pterodactyl->setTarget(tmpTarget+(tmpTarget>0?0.5:0));
	stability = 0;
	//	} else {
	//		stability = 50;
	//	}
	brakeEngagedTime = -1;
}

void AngelChange::Execute() {
	pterodactyl->setOutputRange();
	// Let the PID run.

	if (pterodactyl->isPIDFinished(true) || (target <= 0
			&& pterodactyl->getAngle() <= 0)) {
		stability++;
	} else {
		stability = 0;
	}
	if (tmpTarget == 45 && target < 45 && shooter->isReallyDrawnBack()) {
		tmpTarget = target;
		pterodactyl->setTarget(tmpTarget+(tmpTarget>0 ? 0.5 : 0));
	}
#if ASYNC_BRAKE
	if (stability > 13 && (tmpTarget != 45 || target>45)) {
		brakeEngagedTime = getCurrentMillis();
		if (target > 0) {
			pterodactyl->setBrakeState(Pterodactyl::kActive);
		}
	}
#endif
}

bool AngelChange::IsFinished() {
#if ASYNC_BRAKE
	return brakeEngagedTime > 0 && brakeEngagedTime + 100 < getCurrentMillis();// || IsTimedOut();
#else
	return stability>13;
#endif
}

void AngelChange::End() {
	pterodactyl->setBrakeState(Pterodactyl::kActive);
	pterodactyl->setTarget(tmpTarget);
	pterodactyl->stopPID();
}

void AngelChange::Interrupted() {
	pterodactyl->setBrakeState(Pterodactyl::kActive);
	pterodactyl->setTarget(tmpTarget);
	pterodactyl->stopPID();
}
