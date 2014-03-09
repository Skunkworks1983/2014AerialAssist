#include "FireShooterInternal.h"
#include "../../../Subsystems/Shooter.h"
#include "../../../Robotmap.h"
#include "../../Collector/JawMove.h"
#include "../../../Utils/Commands/CommandStarter.h"

#include "../Latches/SLatch.h"
#include "../Latches/WLatch.h"

FireShooterInternal::FireShooterInternal() :
	CommandGroup("FireShooterInternal") {
	AddSequential(new WLatch(Shooter::kLatched));
	Command *jawMove = new JawMove(Collector::kOpen, 1.25);
	AddSequential(jawMove);
	AddSequential(new SLatch(Shooter::kUnlatched));
	AddSequential(new WaitCommand(1.5));
	AddSequential(new CommandStarter(Shooter::createCreateArmShooter));
}

void FireShooterInternal::Initialize() {
}

void FireShooterInternal::End() {
}

void FireShooterInternal::Interrupted() {
}

