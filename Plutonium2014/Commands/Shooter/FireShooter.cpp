#include "FireShooter.h"
#include "../../Subsystems/Shooter.h"
#include "../../Robotmap.h"
#include "../Collector/JawMove.h"
#include "../../Utils/Commands/CommandStarter.h"

#include "Latches/SLatch.h"
#include "Latches/WLatch.h"

FireShooter::FireShooter() :
	CommandGroup("FireShooter") {
	AddSequential(new WLatch(Shooter::kLatched));
	AddParallel(new JawMove(Collector::kOpen));
	AddSequential(new SLatch(Shooter::kUnlatched));
	AddSequential(new WaitCommand(1.5));
	AddSequential(
			new CommandStarter(Shooter::createCreateArmShooter));
}

void FireShooter::Initialize() {
}

void FireShooter::End() {
}

void FireShooter::Interrupted() {
}

