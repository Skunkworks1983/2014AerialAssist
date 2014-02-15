#include "Shift.h"

#include "../../CommandBase.h"

Shift::Shift(ShiftStyle style) :
			CommandBase(
					CommandBase::createNameFromString(
							"String",
							style == Shift::kToggle ? "Toggle" : (style
									== Shift::kHigh ? "High" : "Low"))) {
	this->style = style;
}

void Shift::Initialize() {
	switch (style) {
	case kLow:
		driveBase->setDriveGear(DriveBase::kLow);
		break;
	case kHigh:
		driveBase->setDriveGear(DriveBase::kHigh);
		break;
	case kToggle:
		driveBase->setDriveGear(
				driveBase->getDriveGear() == DriveBase::kHigh ? DriveBase::kLow
						: DriveBase::kHigh);
		break;
	}
}

void Shift::Execute() {
}

bool Shift::IsFinished() {
	return true;
}

void Shift::End() {
}

void Shift::Interrupted() {
}
