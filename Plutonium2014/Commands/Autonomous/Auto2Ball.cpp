#include "Auto2Ball.h"

#include "../Collector/JawMove.h"
#include "../Pterodactyl/AngelChange.h"
#include "AutoDriveDistance.h"
#include "../Shooter/FireShooter.h"
#include "../Shooter/DrawShooter.h"
#include "../Shooter/ReadyShot.h"
#include "../Collector/Collect.h"

#include "../../Robotmap.h"

Auto2Ball::Auto2Ball() :
	CommandGroup("Auto2Ball") {
	AddSequential(new AngelChange(80)); //All of these magic number need to be less magic
	AddSequential(new FireShooter());
	AddParallel(new AngelChange(0));
	AddSequential(new ReadyShot(2));
	AddParallel(new AutoDriveDistance(5,10,0.5));
	AddSequential(new Collect());
	AddSequential(new FireShooter());
	AddSequential(new DrawShooter());
}
