#include "FireShooter.h"
#include "../../Subsystems/Shooter.h"
#include "../../Robotmap.h"
#include "../Collector/JawMove.h"
#include "../../Utils/Commands/CommandStarter.h"

#include "Latches/SLatch.h"
#include "Latches/WLatch.h"

FireShooter::FireShooter() :
	CommandGroup("FireShooter") {
	AddSequential(new JawMove(Collector::kOpen));
	AddSequential(new WLatch(Shooter::kLatched));
	AddSequential(new SLatch(Shooter::kUnlatched));
	AddSequential(new WaitCommand(1));
	AddSequential(new SLatch(Shooter::kLatched));
//	AddSequential(new CommandStarter(Shooter::createArmShooter));
}

void FireShooter::Initialize() {
}

void FireShooter::End() {
}

