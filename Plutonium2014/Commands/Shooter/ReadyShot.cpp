#include "ReadyShot.h"
#include "../../Robotmap.h"

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
	printf("Kill me now\n");
}

