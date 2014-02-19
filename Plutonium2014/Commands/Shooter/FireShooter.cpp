#include "FireShooter.h"
#include "../../Subsystems/Shooter.h"
#include "../../Robotmap.h"
#include "../Collector/JawMove.h"

#include "Latches/SLatch.h"
#include "Latches/WLatch.h"

FireShooter::FireShooter() :
	CommandGroup("FireShooter") {
	AddSequential(new JawMove(Collector::kOpen));
	AddSequential(new WLatch(Shooter::kLatched));
	AddSequential(new SLatch(Shooter::kUnlatched));
}

void FireShooter::Initialize() {
}

void FireShooter::End() {
}

