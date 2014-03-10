#include "Collect.h"

// Backend
#include "../../Robotmap.h"

// Commands
#include "JawMove.h"
#include "RollerRoll.h"
#include "../Pterodactyl/AngelChange.h"

Collect::Collect() :
	CommandGroup("Collect") {
	//AddParallel(new AngelChange(0));
	AddSequential(new JawMove(Collector::kClosed));
	AddSequential(new RollerRoll(COLLECTOR_ROLLER_INTAKE_SET_POINT));
}
