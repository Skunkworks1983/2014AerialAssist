#include "ReadyShot.h"

// Backend
#include "../../Robotmap.h"

// Commands
#include "DrawShooter.h"
#include "PrepareShooter.h"
#include "../Pterodactyl/AngelChange.h"

ReadyShot::ReadyShot(float setTurns, float angle, float angleThreshold, float shotDelay) :
	CommandGroup("ReadyShot") {
	if (angle > 0) {
		if (angleThreshold > 0) {
			AddParallel((new AngelChange(angle))->setTolerance(angleThreshold));
		} else {
			AddParallel(new AngelChange(angle));
		}
	}
	AddSequential(new DrawShooter());
	AddSequential(new PrepareShooter(setTurns));
	this->shotDelay = shotDelay;
}

void ReadyShot::Initialize() {
	CommandBase::shooter->shootDelay = shotDelay >= 0 ? shotDelay : 0.4; 
}

void ReadyShot::End() {
}

void ReadyShot::Interrupted() {
}

