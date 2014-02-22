#include "../Pterodactyl/AngelChange.h"
#include "../Automatic/AutoDriveDistance.h"
#include "../Shooter/FireShooter.h"
#include "../Shooter/DrawShooter.h"
#include "../Shooter/ReadyShot.h"
#include "../Shooter/PrepareShooter.h"
#include "../Collector/Collect.h"
#include "Autonomous.h"

#include "../../Robotmap.h"

Autonomous *Autonomous::create2Ball(float distance){
	Autonomous *cmd = new Autonomous("Autonomous-2Ball");
	cmd->AddParallel(new PrepareShooter(SHOOTER_POWER_TURNS_2));
	cmd->AddSequential(new AngelChange(80)); //All of these magic number need to be less magic
	cmd->AddSequential(new FireShooter());
	cmd->AddParallel(new AngelChange(0));
	cmd->AddSequential(new ReadyShot(SHOOTER_POWER_TURNS_2));
	cmd->AddParallel(new AutoDriveDistance(5,10,0.5));
	cmd->AddSequential(new Collect());
	cmd->AddSequential(new AngelChange(80));
	cmd->AddSequential(new FireShooter());
	cmd->AddParallel(new AutoDriveDistance(distance,10,0.5));
	cmd->AddSequential(new DrawShooter());
}
