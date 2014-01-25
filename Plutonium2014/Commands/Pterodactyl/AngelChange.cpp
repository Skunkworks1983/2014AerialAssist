#include "AngelChange.h"
#include "../../Robotmap.h"

AngelChange::AngelChange(float target) {	
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(chassis);
	Requires(pterodactyl);
	this->target = target;
}

// Called just before this Command runs the first time
void AngelChange::Initialize() {
	
}

// Called repeatedly when this Command is scheduled to run
void AngelChange::Execute() {
	if(pterodactyl->getAngle() < (target+LIL_BIT)){ //within half a degree so the pterodactyl doesn't swing indefinately
		pterodactyl->setAngleMotorSpeed(.25);
	}
	else if(pterodactyl->getAngle() > (target-LIL_BIT)){
		pterodactyl->setAngleMotorSpeed(-.25);
	}
	if(pterodactyl->getAngle()<(target+THRESHOLD_LOWER) && (target-LIL_BIT) < pterodactyl->getAngle()){ //if the current angle is past the lower threshold and going down
		pterodactyl->setAngleMotorSpeed(-0.125);
	}
	else if(pterodactyl->getAngle()>(target-THRESHOLD_UPPER) && (target+LIL_BIT) > pterodactyl->getAngle()){
		pterodactyl->setAngleMotorSpeed(0.125);
	}
}

// Make this return true when this Command no longer needs to run execute()
bool AngelChange::IsFinished() {
	if((pterodactyl->getAngle() < (target+LIL_BIT) && pterodactyl->getAngle() > (target-LIL_BIT)) 
			|| pterodactyl->getLimNeg() == true || pterodactyl->getLimPos() == true){ //checks if current angle is near target and stops
		return true;
	}
	return false;
}

// Called once after isFinished returns true
void AngelChange::End() {
	pterodactyl->setAngleMotorSpeed(0);
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void AngelChange::Interrupted() {
}
