#include "AngelChange.h"
#include "../../Robotmap.h"
#include <math.h>

AngelChange::AngelChange(float target) :
	CommandBase(CommandBase::createNameFromFloat("AngleChange", target)) {
	Requires(pterodactyl);
	this->target = target;
	this->stability = 0;
	SetInterruptible(true);
}

void AngelChange::Initialize() {
//	if ((fabs(target - pterodactyl->getAngle())) > PTERODACTYL_ANGLE_THRESHOLD) {
		pterodactyl->setBrakeState(Pterodactyl::kDeactive);
		tmpTarget = target;
		if (tmpTarget < 45 && shooter->getTurns() > 0.25
				&& !shooter->isReallyDrawnBack()) {
			tmpTarget = 45;//Safeties  Collector shouldn't go down in this case
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
		pterodactyl->stopPID();
		pterodactyl->writeAngleMotorRaw(0.0);
		pterodactyl->setBrakeState(Pterodactyl::kDeactive);
	}
}

bool AngelChange::IsFinished() {
	return stability > 15;
}

void AngelChange::End() {
	pterodactyl->stopPID();
	pterodactyl->setBrakeState(Pterodactyl::kActive);
}

void AngelChange::Interrupted() {
	printf("Interrupting angels\n");
	pterodactyl->stopPID();
	pterodactyl->setBrakeState(Pterodactyl::kActive);
}
