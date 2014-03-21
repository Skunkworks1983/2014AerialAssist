#include "AngelChange.h"
// CSTDLIB
#include <math.h>

// Backend
#include "../../Robotmap.h"

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
	tmpTarget = target;
	if (tmpTarget < 45 && shooter->getTurns() > 0.25 && !shooter->isReallyDrawnBack()) {
		//tmpTarget = 45; //Safeties  Collector shouldn't go down in this case
	}
	pterodactyl->setTarget(tmpTarget);
	stability = 0;
	//	} else {
	//		stability = 50;
	//	}
}

void AngelChange::Execute() {
	pterodactyl->setOutputRange();

	SmartDashboard::PutNumber("pteroangle", pterodactyl->getAngle());
	SmartDashboard::PutNumber("pterorate", pterodactyl->getRate());
	SmartDashboard::PutNumber("Pteroerror", pterodactyl->getAngle()
			-pterodactyl->getTarget());
	// Let the PID run.

	if (pterodactyl->isPIDFinished() || (target <= 0 && pterodactyl->getAngle()
			<= 0)) {
		stability++;
	} else {
		stability = 0;
	}
	if (tmpTarget == 45 && target < 45 && shooter->isReallyDrawnBack()) {
		tmpTarget = target;
		pterodactyl->setTarget(tmpTarget);
	}
	if (target <= 0 && pterodactyl->getAngle() < 10) {
		//pterodactyl->stopPID();
		//pterodactyl->writeAngleMotorRaw(0.0);
		pterodactyl->setBrakeState(Pterodactyl::kDeactive);
	}
}

bool AngelChange::IsFinished() {
	return stability > 13;// || IsTimedOut();
}

void AngelChange::End() {
	pterodactyl->setBrakeState(Pterodactyl::kActive);
	pterodactyl->stopPID();
}

void AngelChange::Interrupted() {
	pterodactyl->setBrakeState(Pterodactyl::kActive);
	pterodactyl->stopPID();
}
