#include "Pass.h"

#include "JawMove.h"
#include "RollerRoll.h"
#include "../Pterodactyl/AngelChange.h"

#include "../../Robotmap.h"
//#include "RobotMap.h"

Pass::Pass(): 
	CommandGroup("Pass") {
	AddSequential(new AngelChange(0));
	AddSequential(new JawMove(false));
	AddSequential(new RollerRoll(-COLLECTOR_ROLLER_INTAKE_SET_POINT));
	AddSequential(new JawMove(true));
}

//Reload::~Reload() {
//}
