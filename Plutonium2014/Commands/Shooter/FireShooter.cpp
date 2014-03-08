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
	Command *jawMove = new JawMove(Collector::kOpen, 1.25);
	AddSequential(jawMove);
	AddSequential(new SLatch(Shooter::kUnlatched));
	AddSequential(new WaitCommand(1.5));
	AddSequential(new CommandStarter(Shooter::createCreateArmShooter));
}

void FireShooter::Initialize() {
	if (CommandBase::pterodactyl->getAngle() < 45 || CommandBase::pterodactyl->getPIDTarget() < 45) {
		Cancel();
	}
}

void FireShooter::End() {
}

void FireShooter::Interrupted() {
}

