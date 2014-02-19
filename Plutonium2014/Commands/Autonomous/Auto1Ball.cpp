#include "Auto1Ball.h"

#include "../Collector/JawMove.h"
#include "../Pterodactyl/AngelChange.h"
#include "AutoDriveDistance.h"
#include "../Shooter/FireShooter.h"
#include "../Shooter/DrawShooter.h"
#include "HotGoalWait.h"

#include "../../Robotmap.h"

Auto1Ball::Auto1Ball() :
	CommandGroup("Auto1Ball") {
	AddSequential(new AutoDriveDistance(5,10,0.5)); //All of these magic number need to be less magic
	//AddSequential(new HotGoalWait());
	AddSequential(new AngelChange(80));
	AddSequential(new FireShooter());
	AddSequential(new DrawShooter());
}
