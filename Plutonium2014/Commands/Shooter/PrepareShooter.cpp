#include "PrepareShooter.h"
#include "../../Subsystems/Shooter.h"
#include "../../Robotmap.h"

#include "Latches/WLatch.h"
#include "Raw/ReleaseTension.h"

PrepareShooter::PrepareShooter(float setTurns) :
	CommandGroup("PrepareShooter") {
	AddSequential(new WLatch(Shooter::kUnlatched));
	AddSequential(new ReleaseTension(setTurns));
	AddSequential(new WLatch(Shooter::kLatched));
}

void PrepareShooter::Initialize() {
	SetInterruptible(false);
}

void PrepareShooter::End() {
	//CommandBase::shooter->setPrepared(true);
}

