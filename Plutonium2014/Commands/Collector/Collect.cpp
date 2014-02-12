#include "Collect.h"

#include "JawMove.h"
#include "RollerRoll.h"

#include "../../Robotmap.h"
//#include "RobotMap.h"

Collect::Collect(): 
	CommandGroup("Collect") {
	AddSequential(new JawMove(true));
	AddSequential(new RollerRoll(COLLECTOR_ROLLER_INTAKE_SET_POINT));
//dun worry bebe everything is defined in the roller roll crispy chicken swag swag muda
	AddSequential(new JawMove(false));
}

//Reload::~Reload() {
//}
