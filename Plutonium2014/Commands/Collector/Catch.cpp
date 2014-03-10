#include "Catch.h"

// Backend
#include "../../Robotmap.h"

// Commands
#include "JawMove.h"
#include "RollerRoll.h"
#include "../Pterodactyl/AngelChange.h"

Catch::Catch(float angle): 
	CommandGroup("Catch") {
	AddParallel(new AngelChange(angle));
	AddSequential(new JawMove(Collector::kOpen));
	AddSequential(new RollerRoll(COLLECTOR_ROLLER_INTAKE_SET_POINT));
}

