#include "FireZeMissle.h"
#include "../../Subsystems/Shootah.h"
#include "../../Robotmap.h"
#include "../Collector/JawMove.h"

#include "Latches/SLatch.h"
#include "Latches/WLatch.h"

FireZeMissle::FireZeMissle() :
	CommandGroup("FireZeMissle") {
	AddSequential(new JawMove(Collector::kOpen));
	AddSequential(new WLatch(Shootah::kLatched));
	AddSequential(new SLatch(Shootah::kUnlatched));
}

void FireZeMissle::Initialize() {
}

void FireZeMissle::End() {
}

