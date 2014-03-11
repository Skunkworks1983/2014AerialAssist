#include "Pass.h"

// WPILib
#include "Commands/WaitCommand.h"

// Backend
#include "../../Robotmap.h"

// Commands
#include "JawMove.h"
#include "RollerRoll.h"
#include "../Pterodactyl/AngelChange.h"

Pass::Pass(): 
	CommandGroup("Pass") {
//	AddParallel(new AngelChange(10));
	AddParallel(new JawMove(Collector::kOpen));
	AddSequential(new WaitCommand(0.1));
	AddSequential(new RollerRoll(-COLLECTOR_ROLLER_INTAKE_SET_POINT));
}

