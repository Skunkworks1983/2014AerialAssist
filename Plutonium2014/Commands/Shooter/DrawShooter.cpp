#include "DrawShooter.h"

// Backend
#include "../../Subsystems/Shooter.h"
#include "../../Robotmap.h"

// Commands
#include "Latches/SLatch.h"
#include "Latches/WLatch.h"
#include "Raw/FullTension.h"

DrawShooter::DrawShooter() :
	CommandGroup("DrawShooter") {
	AddSequential(new SLatch(Shooter::kLatched));
	AddSequential(new WLatch(Shooter::kUnlatched));
	AddSequential(new FullTension());
}

void DrawShooter::Initialize() {
}

void DrawShooter::End() {
	//CommandBase::shooter->setPrepared(false);
}

