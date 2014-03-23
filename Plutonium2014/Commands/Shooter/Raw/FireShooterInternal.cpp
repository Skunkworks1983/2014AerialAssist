#include "FireShooterInternal.h"
// Utils
#include "../../../Utils/Commands/CommandStarter.h"

// Backend
#include "../../../Subsystems/Shooter.h"
#include "../../../Robotmap.h"

// Commands
#include "../../Collector/JawMove.h"
#include "../Latches/SLatch.h"
#include "../../Pterodactyl/DiscBrake.h"
#include "../Latches/WLatch.h"

FireShooterInternal::FireShooterInternal(bool autoArm) :
	CommandGroup("FireShooterInternal") {
	AddSequential(new DiscBrake(Pterodactyl::kActive));
	AddSequential(new WLatch(Shooter::kLatched));
	Command *jawMove = new JawMove(Collector::kOpen, 0.5);
	AddSequential(jawMove);
	AddSequential(new SLatch(Shooter::kUnlatched));
	if (autoArm) {
		AddSequential(new CommandStarter(Shooter::createCreateArmShooter));
	}
}

void FireShooterInternal::Initialize() {
}

void FireShooterInternal::End() {
}

void FireShooterInternal::Interrupted() {
}

