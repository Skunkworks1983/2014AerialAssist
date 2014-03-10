#include "ReadyShot.h"

// Backend
#include "../../Robotmap.h"

// Commands
#include "DrawShooter.h"
#include "PrepareShooter.h"

ReadyShot::ReadyShot(float setTurns) :
	CommandGroup("ReadyShot") {
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

