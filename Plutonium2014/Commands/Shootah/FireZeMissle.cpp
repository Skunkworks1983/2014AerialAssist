#include "FireZeMissle.h"
#include "../../Subsystems/Shootah.h"
#include "../../Robotmap.h"

#include "Latches/SLatch.h"

FireZeMissle::FireZeMissle() :
	CommandGroup("FireZeMissle") {
	AddSequential(new SLatch(false));
}

void FireZeMissle::Initialize() {
}

void FireZeMissle::End() {
	//CommandBase::shootah->setPrepared(false);
}

