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
	double n = 1.0;
	double a = (oi->getJoystickRight()->GetAxis(Joystick::kYAxis) + oi->getJoystickLeft()->GetAxis(Joystick::kYAxis));
	double b = (oi->getJoystickRight()->GetAxis(Joystick::kYAxis) - oi->getJoystickLeft()->GetAxis(Joystick::kYAxis));
	
	double scale = (pow(a,n)/2*b/2);
	
	driveBase->setSpeed(oi->getJoystickLeft()->GetAxis(Joystick::kYAxis) + oi->getJoystickRight()->GetAxis(Joystick::kYAxis)*scale
			, oi->getJoystickRight()->GetAxis(Joystick::kYAxis) - oi->getJoystickRight()->GetAxis(Joystick::kYAxis)*scale);
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
