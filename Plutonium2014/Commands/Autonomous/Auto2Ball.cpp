#include "Autonomous.h"
// Backend
#include "../../Robotmap.h"

// Commands
#include "../Pterodactyl/AngelChange.h"
#include "../Automatic/AutoDriveDistance.h"
#include "../Shooter/FireShooter.h"
#include "../Shooter/DrawShooter.h"
#include "../Shooter/ReadyShot.h"
#include "../Shooter/PrepareShooter.h"
#include "../Automatic/HotGoalWait.h"
#include "../Collector/Collect.h"

Autonomous *Autonomous::create2Ball(float distance){
	Autonomous *cmd = new Autonomous("Autonomous-2Ball");
	cmd->AddParallel(new PrepareShooter(1.0));
	cmd->AddSequential(new AngelChange(80)); //All of these magic number need to be less magic
	cmd->AddSequential(new FireShooter());
	cmd->AddParallel(new AngelChange(0));
	cmd->AddSequential(new ReadyShot(1.0));
	cmd->AddParallel(new AutoDriveDistance(5,10,0.5));
	cmd->AddSequential(new Collect());
	cmd->AddSequential(new AngelChange(80));
	cmd->AddSequential(new FireShooter());
	cmd->AddParallel(new AutoDriveDistance(distance,10,0.5));
	cmd->AddSequential(new DrawShooter());
	return cmd;
}
