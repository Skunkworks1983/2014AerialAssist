#include "TankDrive.h"
// CSTDLIB
#include <math.h>

// WPILib
#include "Joystick.h"

// Backend
#include "../../Robotmap.h"
#include "../../CommandBase.h"

TankDrive::TankDrive() :
		CommandBase("TankDrive") {
	Requires(driveBase);
}

void TankDrive::Initialize() {
	driveBase->setSpeed(0, 0);
}

void TankDrive::Execute() {
	double left = -oi->getJoystickLeft()->GetAxis(Joystick::kYAxis);
	double right = -oi->getJoystickRight()->GetAxis(Joystick::kYAxis);
	if (fabs(left) < OI_JOYSTICK_DRIVE_DEADBAND) {
		left = 0;
	}
	if (fabs(right) < OI_JOYSTICK_DRIVE_DEADBAND) {
		right = 0;
	}

	double sum = (left + right);
	double error = (left - right);

	double favgSpeed = fabs(sum / 2);
	double scale = pow(favgSpeed, OI_JOYSTICK_SQUIRRLY_POWER) / 2;

	left = left - (error * scale);
	right = right + (error * scale);

	driveBase->setSpeed(left, right);
}

bool TankDrive::IsFinished() {
	//WHEN DOES THE PAIN END?!
	return false;
}

void TankDrive::End() {
	driveBase->setSpeed(0, 0);
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void TankDrive::Interrupted() {
}
