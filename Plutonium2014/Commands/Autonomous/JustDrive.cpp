#include "Autonomous.h"
// Backend
#include "../../Robotmap.h"

// Commands
#include "../Automatic/AutoDriveDistance.h"

Autonomous *Autonomous::createJustDrive(float distance){
	Autonomous *cmd = new Autonomous("Autonomous-JustDrive");
	cmd->AddSequential(new AutoDriveDistance(20,2,5));
	return cmd;
}
