#include "Auto2Ball.h"

#include "../Pterodactyl/AngelChange.h"
#include "AutoDriveDistance.h"
#include "../Shooter/FireShooter.h"
#include "../Shooter/DrawShooter.h"
#include "../Shooter/ReadyShot.h"
#include "../Shooter/PrepareShooter.h"
#include "../Collector/Collect.h"

#include "../../Robotmap.h"

Auto2Ball::Auto2Ball() :
	CommandGroup("Auto2Ball") {
	AddParallel(new PrepareShooter(SHOOTER_POWER_TURNS_2));
	AddSequential(new AngelChange(80)); //All of these magic number need to be less magic
	AddSequential(new FireShooter());
	AddParallel(new AngelChange(0));
	AddSequential(new ReadyShot(SHOOTER_POWER_TURNS_2));
	AddParallel(new AutoDriveDistance(5,10,0.5));
	AddSequential(new Collect());
	AddSequential(new AngelChange(80));
	AddSequential(new FireShooter());
	AddSequential(new DrawShooter());
}
