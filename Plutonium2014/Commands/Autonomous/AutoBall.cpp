#include "AutoBall.h"

#include "../Pterodactyl/AngelChange.h"
#include "AutoDriveDistance.h"
#include "../Shooter/FireShooter.h"
#include "../Shooter/DrawShooter.h"
#include "../Shooter/ReadyShot.h"
#include "../Collector/Collect.h"

#include "../../Robotmap.h"

AutoBall::AutoBall(int ballCount) :
	CommandGroup("AutoBall") {
	AddParallel(new ReadyShot(SHOOTER_POWER_TURNS_2));
	AddSequential(new AngelChange(AUTO_SHOT_ANGLE)); //All of these magic number need to be less magic
	AddSequential(new FireShooter());
	for(int i =1; i < ballCount; i++){
		AddParallel(new AngelChange(0));
		AddSequential(new ReadyShot(SHOOTER_POWER_TURNS_2));
		AddParallel(new AutoDriveDistance(5,10,0.5));
		AddSequential(new Collect());
		AddSequential(new AngelChange(AUTO_SHOT_ANGLE + ((i)*AUTO_SHOT_SCALAR))); //Only works with linear
		AddSequential(new FireShooter());
	}
	AddParallel(new AutoDriveDistance(5,10,0.5));
	AddParallel(new DrawShooter());
	AddSequential(new AngelChange(0));
}
