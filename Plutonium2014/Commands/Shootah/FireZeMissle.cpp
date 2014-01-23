#include "FireZeMissle.h"

FireZeMissle::FireZeMissle() {
	Requires(shootah);
	// Requires collector?
}

// Called just before this Command runs the first time
void FireZeMissle::Initialize() {
	
}

// Called repeatedly when this Command is scheduled to run
void FireZeMissle::Execute() {
	
}

// Make this return true when this Command no longer needs to run execute()
bool FireZeMissle::IsFinished() {
	return false;
}

// Called once after isFinished returns true
void FireZeMissle::End() {
	
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void FireZeMissle::Interrupted() {
}
