#include "Catch.h"

Catch::Catch() {
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(chassis);
}

// Called just before this Command runs the first time
void Catch::Initialize() {
	
}

// Called repeatedly when this Command is scheduled to run
void Catch::Execute() {
	
}

// Make this return true when this Command no longer needs to run execute()
bool Catch::IsFinished() {
	return false;
}

// Called once after isFinished returns true
void Catch::End() {
	
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void Catch::Interrupted() {
}
