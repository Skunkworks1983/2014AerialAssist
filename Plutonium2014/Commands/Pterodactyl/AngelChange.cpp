#include "AngelChange.h"

AngelChange::AngelChange() {
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(chassis);
}

// Called just before this Command runs the first time
void AngelChange::Initialize() {
	
}

// Called repeatedly when this Command is scheduled to run
void AngelChange::Execute() {
	
}

// Make this return true when this Command no longer needs to run execute()
bool AngelChange::IsFinished() {
	return false;
}

// Called once after isFinished returns true
void AngelChange::End() {
	
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void AngelChange::Interrupted() {
}
