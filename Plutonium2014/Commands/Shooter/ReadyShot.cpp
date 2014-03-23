#include "ReadyShot.h"

// Backend
#include "../../Robotmap.h"

// Commands
#include "DrawShooter.h"
#include "PrepareShooter.h"
#include "../Pterodactyl/AngelChange.h"

ReadyShot::ReadyShot(float setTurns, float angle) :
	CommandGroup("ReadyShot") {
	if (angle > 0) {
		AddParallel(new AngelChange(angle));
	}
	AddSequential(new DrawShooter());
	AddSequential(new PrepareShooter(setTurns));
	SetInterruptible(false);
}

void ReadyShot::Initialize() {
}

void ReadyShot::End() {
}

void ReadyShot::Interrupted() {
}

