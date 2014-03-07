#include "Pass.h"

#include "JawMove.h"
#include "RollerRoll.h"
#include "../Pterodactyl/AngelChange.h"
#include "Commands/WaitCommand.h"
#include "../../Robotmap.h"
//#include "RobotMap.h"

Pass::Pass(): 
	CommandGroup("Pass") {
//	AddParallel(new AngelChange(10));
	AddParallel(new JawMove(Collector::kOpen));
	AddSequential(new WaitCommand(0.1));
	AddSequential(new RollerRoll(-COLLECTOR_ROLLER_INTAKE_SET_POINT));
}

