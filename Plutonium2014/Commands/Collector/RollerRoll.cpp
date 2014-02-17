#include "RollerRoll.h"
#include "../../Utils/Time.h"

RollerRoll::RollerRoll(float speed) :
	CommandBase(CommandBase::createNameFromFloat("RollerRoll", speed)) {
	Requires(collector);
	this->speed = speed;
	this->timeWait = 0;
}

void RollerRoll::Initialize() {
	collector->setRollerSpeed(speed);
	//collector->PIDWrite(0.9);
}

void RollerRoll::Execute() {
	//printf("DesiredSpeed: %f\tSpeed: %f\tDistance: %f\tisBallDetected: %d \n ", speed,
	//		collector->getRollerSpeed(), collector->getRollerDistance(), collector->isBallDetected());

	if (!collector->isBallDetected() && speed <= 0 && timeWait == 0) {
		timeWait = getCurrentMillis();
		printf("TIME STERTED at: %f", timeWait);
	}
	SmartDashboard::PutNumber("RollerSpeed", collector->getRollerSpeed());
}

bool RollerRoll::IsFinished() {
	printf("Difference: %f", getCurrentMillis() - timeWait);
	return (collector->isBallDetected() && speed >= 0)
			|| ((!collector->isBallDetected() && speed <= 0)
					&& (getCurrentMillis()- timeWait >= 1000));
}

void RollerRoll::End() {
	collector->setRollerSpeed(0.0);
	//collector->PIDWrite(0);
}

void RollerRoll::Interrupted() {
	collector->setRollerSpeed(0.0);
	//collector->PIDWrite(0);
}
