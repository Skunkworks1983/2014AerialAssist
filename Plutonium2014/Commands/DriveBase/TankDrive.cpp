#include "TankDrive.h"
#include "WPILib.h"
#include "JoyStick.h"
#include <cmath>
#include "../../CommandBase.h"

TankDrive::TankDrive() {
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(chassis);
	Requires(driveBase);
}

// Called just before this Command runs the first time
void TankDrive::Initialize() {
	driveBase->setSpeed(0, 0);
}

// Called repeatedly when this Command is scheduled to run
void TankDrive::Execute() {
	double left = oi->getJoystickLeft()->GetAxis(Joystick::kYAxis);
	double right = oi->getJoystickRight()->GetAxis(Joystick::kYAxis);
	double n = 2.0;
	double sum = (right + left);
	double error = (right - left);
	left = left + (error * scale);
	right = right - (error * scale);
	favgSpeed = fabs(sum / 2);
	scale = pow(favgSpeed, n);
	
	double scale = (pow(sum, n) / 2 * error / 2);

	driveBase->setSpeed(left + right * scale, right - left * scale);
}

// Make this return true when this Command no longer needs to run execute()
bool TankDrive::IsFinished() {
	//WHEN DOES THE PAIN END?!
	return false;
}

// Called once after isFinished returns true
void TankDrive::End() {
	driveBase->setSpeed(0, 0);
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void TankDrive::Interrupted() {
}
