#include "AngelChange.h"
#include "../../Robotmap.h"
#include <math.h>

AngelChange::AngelChange(float target) : CommandBase(CommandBase::createNameFromFloat("AngleChange",target)){
	Requires(pterodactyl);
	this->target = target;
}

void AngelChange::Initialize() {
}

void AngelChange::Execute() {
	if(pterodactyl->getAngle() < (target+LIL_BIT)){ //within half a degree so the pterodactyl doesn't swing indefinately
	 pterodactyl->setAngleMotorSpeed(PTERODACTYL_UP);
	 }
	 else if(pterodactyl->getAngle() > (target-LIL_BIT)){
	 pterodactyl->setAngleMotorSpeed(PTERODACTYL_DOWN);
	 }
	 if(pterodactyl->getAngle()<(target+THRESHOLD_LOWER) && (target-LIL_BIT) < pterodactyl->getAngle()){ //if the current angle is past the lower threshold and going down
	 pterodactyl->setAngleMotorSpeed(PTERODACTYL_DOWN_NEAR);
	 }
	 else if(pterodactyl->getAngle()>(target-THRESHOLD_UPPER) && (target+LIL_BIT) > pterodactyl->getAngle()){
	 pterodactyl->setAngleMotorSpeed(PTERODACTYL_UP_NEAR);
	 }
}

bool AngelChange::IsFinished() {
	return fabs((pterodactyl->getAngle()-target) < LIL_BIT 
	 ||  target<pterodactyl->getAngle()
	 ||  target>pterodactyl->getAngle()); //checks if current angle is near target and stops
}

void AngelChange::End() {
	pterodactyl->setAngleMotorSpeed(0);
}

void AngelChange::Interrupted() {
	pterodactyl->setAngleMotorSpeed(0);
}
