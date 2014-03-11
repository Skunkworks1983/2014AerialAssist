#include "Autonomous.h"
// Backend
#include "../../Robotmap.h"

// Commands
#include "../Pterodactyl/AngelChange.h"
#include "../Automatic/AutoDriveDistance.h"
#include "../Shooter/FireShooter.h"
#include "../Shooter/DrawShooter.h"
#include "../Shooter/PrepareShooter.h"
#include "../Shooter/ReadyShot.h"
#include "../Automatic/HotGoalWait.h"
#include "../Collector/Collect.h"

Autonomous *Autonomous::createAutoBall(int ballCount, float distance){
	Autonomous *cmd = new Autonomous("Autonomous-AutoBall");
	cmd->AddParallel(new ReadyShot(SHOOTER_POWER_TURNS_2));
	cmd->AddSequential(new AngelChange(AUTO_SHOT_ANGLE)); //All of these magic number need to be less magic
	cmd->AddSequential(new FireShooter());
	for(int i =1; i < ballCount; i++){
		cmd->AddParallel(new AngelChange(0));
		cmd->AddSequential(new ReadyShot(SHOOTER_POWER_TURNS_2));
		cmd->AddParallel(new AutoDriveDistance(5,10,0.5));
		cmd->AddSequential(new Collect());
		cmd->AddSequential(new AngelChange(AUTO_SHOT_ANGLE + ((i)*AUTO_SHOT_SCALAR))); //Only works with linear
		cmd->AddSequential(new FireShooter());
	}
	cmd->AddSequential(new AutoDriveDistance(5,10,0.5)); //This crosses the line
	cmd->AddParallel(new AutoDriveDistance(distance,10,0.5));
	cmd->AddParallel(new DrawShooter());
	cmd->AddSequential(new AngelChange(0));
	return cmd;
}
