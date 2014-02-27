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
	if ((fabs(target - pterodactyl->getAngle())) > PTERODACTYL_ANGLE_THRESHOLD) {
		pterodactyl->setBrakeState(Pterodactyl::kDeactive);
		pterodactyl->setTarget(target);
	}
	stability=0;
}

void AngelChange::Execute() {
	pterodactyl->setOutputRange();
	SmartDashboard::PutNumber("pteroangle: ", pterodactyl->getAngle());
	SmartDashboard::PutNumber("pterorate: ", pterodactyl->getRate());
	// Let the PID run.
}

bool AngelChange::IsFinished() {
	if (pterodactyl->isPIDFinished()) {
		stability++;
	} else {
		stability=0;
	}
	if (target <= 0 && pterodactyl->getAngle() < 10) {
		pterodactyl->stopPID();
		pterodactyl->setBrakeState(Pterodactyl::kDeactive);
	}
	return stability > (target<=0 ? 10 : 5);
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
