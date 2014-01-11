#include "Shift.h"

Shift::Shift() {
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(chassis);
}

// Called just before this Command runs the first time
void Shift::Initialize() {
	
}

// Called repeatedly when this Command is scheduled to run
void Shift::Execute() {
	
}

// Make this return true when this Command no longer needs to run execute()
bool Shift::IsFinished() {
	return false;
}

// Called once after isFinished returns true
void Shift::End() {
	
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void Shift::Interrupted() {
}
