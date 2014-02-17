#include "ReadyShot.h"
#include "../../Robotmap.h"

#include "DrawZeDevice.h"
#include "PrepareZeDevice.h"

ReadyShot::ReadyShot(float setTurns) :
	CommandGroup("ReadyShot") {
	AddSequential(new DrawZeDevice());
	AddSequential(new PrepareZeDevice(setTurns));
}

void ReadyShot::Initialize() {
	SetInterruptible(false);
}

void ReadyShot::End() {
}

