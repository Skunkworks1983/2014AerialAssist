#include "AngelChange.h"
#include "../../Robotmap.h"
#include <math.h>

AngelChange::AngelChange(float target) :
	CommandBase(CommandBase::createNameFromFloat("AngleChange", target)) {
	Requires(pterodactyl);
	this->target = target;
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
	/*if (pterodactyl->getAngle() < (target + LIL_BIT)) { //within half a degree so the pterodactyl doesn't swing indefinately
	 pterodactyl->setAngleMotorSpeed(PTERODACTYL_UP);
	 } else if (pterodactyl->getAngle() > (target - LIL_BIT)) {
	 pterodactyl->setAngleMotorSpeed(PTERODACTYL_DOWN);
	 }
	 if (pterodactyl->getAngle() < (target + THRESHOLD_LOWER) && (target
	 - LIL_BIT) < pterodactyl->getAngle()) { //if the current angle is past the lower threshold and going down
	 pterodactyl->setAngleMotorSpeed(PTERODACTYL_DOWN_NEAR);
	 } else if (pterodactyl->getAngle() > (target - THRESHOLD_UPPER) && (target
	 + LIL_BIT) > pterodactyl->getAngle()) {
	 pterodactyl->setAngleMotorSpeed(PTERODACTYL_UP_NEAR);
	 }*/

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
