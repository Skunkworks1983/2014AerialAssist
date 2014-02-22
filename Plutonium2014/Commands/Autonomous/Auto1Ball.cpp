#include "Auto1Ball.h"

#include "../Pterodactyl/AngelChange.h"
#include "AutoDriveDistance.h"
#include "../Shooter/FireShooter.h"
#include "../Shooter/DrawShooter.h"
#include "../Shooter/PrepareShooter.h"
#include "HotGoalWait.h"

#include "../../Robotmap.h"

Auto1Ball::Auto1Ball() :
	CommandGroup("Auto1Ball") {
	AddParallel(new PrepareShooter(SHOOTER_POWER_TURNS_2));
	AddSequential(new AngelChange(80));
	//AddSequential(new HotGoalWait());
	AddSequential(new FireShooter());
	AddParallel(new AutoDriveDistance(5,10,0.5)); //All of these magic number need to be less magic
	AddParallel(new AngelChange(0));
	AddSequential(new DrawShooter());
}
