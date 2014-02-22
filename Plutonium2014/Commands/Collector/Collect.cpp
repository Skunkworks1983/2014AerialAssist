#include "Collect.h"

#include "JawMove.h"
#include "RollerRoll.h"
#include "../Pterodactyl/AngelChange.h"

#include "../../Robotmap.h"

Collect::Collect() :
	CommandGroup("Collect") {
	AddSequential(new JawMove(Collector::kClosed));
	AddSequential(new RollerRoll(COLLECTOR_ROLLER_INTAKE_SET_POINT));
}
