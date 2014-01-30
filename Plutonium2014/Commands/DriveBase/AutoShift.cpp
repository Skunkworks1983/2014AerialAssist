#include "AutoShift.h"

#include "../../CommandBase.h"
#include "../../Robotmap.h"

void AutoShift::Initialize() {
	loopCount = 0;
}

void AutoShift::Execute() {
	loopCount++;
	if (loopCount < 100) {
		return;
	}
	loopCount = 0;
	if (driveBase->getMotorSpeed() > MOTOR_MAX
			&& ((driveBase->getLeftEncoder()->GetRate()
					+ driveBase->getRightEncoder()->GetRate()) / 2)
					< TOO_DAMN_SLOW && driveBase->getDriveGear() == DriveBase::kLow) {
		driveBase->setDriveGear(DriveBase::kHigh);
	} else if (driveBase->getMotorSpeed() > MOTOR_MAX
			&& ((driveBase->getLeftEncoder()->GetRate()
					+ driveBase->getRightEncoder()->GetRate()) / 2)
					< TOO_DAMN_SLOW && driveBase->getDriveGear() == DriveBase::kHigh) {
		driveBase->setDriveGear(DriveBase::kLow);
	}
}

bool AutoShift::IsFinished() {
	return false;
}

void AutoShift::End() {
}

void AutoShift::Interrupted() {
}
