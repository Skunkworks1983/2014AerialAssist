#include "Catch.h"

#include "JawMove.h"
#include "RollerRoll.h"
#include "../Pterodactyl/AngelChange.h"

#include "../../Robotmap.h"

Catch::Catch(float angle): 
	CommandGroup("Catch") {
	AddParallel(new JawMove(Collector::kOpen));
	AddParallel(new AngelChange(angle));
}

