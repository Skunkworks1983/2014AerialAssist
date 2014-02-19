#include "DrawShooter.h"
#include "../../Subsystems/Shooter.h"
#include "../../Robotmap.h"

#include "Latches/SLatch.h"
#include "Latches/WLatch.h"
#include "Raw/FullTension.h"

DrawShooter::DrawShooter() :
	CommandGroup("DrawShooter") {
	AddSequential(new SLatch(Shooter::kLatched));
	AddSequential(new WLatch(Shooter::kUnlatched));
	AddSequential(new FullTension());
	//AddSequential(new WLatch(Shooter::kLatched));
}

void DrawShooter::Initialize() {
	SetInterruptible(false);
}

void DrawShooter::End() {
	//CommandBase::shooter->setPrepared(false);
}

