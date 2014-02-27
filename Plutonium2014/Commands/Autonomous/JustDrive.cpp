#include "../Pterodactyl/AngelChange.h"
#include "../Automatic/AutoDriveDistance.h"
#include "Autonomous.h"

#include "../../Robotmap.h"

Autonomous *Autonomous::createJustDrive(float distance){
	Autonomous *cmd = new Autonomous("Autonomous-JustDrive");
	//cmd->AddParallel(new AngelChange(0));
	cmd->AddSequential(new AutoDriveDistance(20,10,2)); //This crosses the line
	//cmd->AddSequential(new AutoDriveDistance(distance,10,0.5));
	return cmd;
}
