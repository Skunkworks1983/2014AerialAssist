#include "FireZeMissle.h"
#include "../../Subsystems/Shootah.h"
#include "../../Robotmap.h"
#include "../Collector/JawMove.h"

#include "Latches/SLatch.h"

FireZeMissle::FireZeMissle() :
	CommandGroup("FireZeMissle") {
	AddSequential(new JawMove(true));
	AddSequential(new SLatch(Shootah::kUnlatched));
}

void FireZeMissle::Initialize() {
}

void FireZeMissle::End() {
}

