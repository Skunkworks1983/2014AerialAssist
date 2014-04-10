// Commands
#include "Autonomous.h"
#include "../../ShotTuning.h"
#include "../Pterodactyl/AngelChange.h"
#include "../Automatic/AutoDriveDistance.h"
#include "../Collector/JawMove.h"
#include "../Shooter/Raw/FireShooterInternal.h"
#include "../Shooter/DrawShooter.h"
#include "../Shooter/PrepareShooter.h"
#include "../Automatic/HotGoalWait.h"
#include "AutoStupidDrive.h"
#include "../Collector/JawMove.h"
#include "../Shooter/Latches/SLatch.h"
#include "../Pterodactyl/DiscBrake.h"
#include "../Shooter/Latches/WLatch.h"

Autonomous *Autonomous::createDerpy() {
	Autonomous *cmd = new Autonomous("Derpy");
	CommandGroup *drive = new CommandGroup("Drive");
	CommandGroup *prepare = new CommandGroup("CHILD");

	prepare->AddParallel(new PrepareShooter(NEAR_SHOT_POWER));
	prepare->AddSequential(new AngelChange(0,1));
	prepare->AddSequential(new AngelChange(NEAR_SHOT_ANGLE+1.5,5));

	//	prepare->AddSequential(new JawMove(Collector::kOpen, 1));

	drive->AddParallel(prepare);
	drive->AddSequential(new AutoStupidDrive(2.5,.375)); //All of these magic number need to be less magic
	cmd->AddSequential(drive);
	cmd->AddSequential(new WaitCommand(0.5));

	// Fire Shooter Internal
	cmd->AddSequential(new DiscBrake(Pterodactyl::kActive));
	cmd->AddSequential(new WLatch(Shooter::kLatched));
	cmd->AddSequential(new JawMove(Collector::kOpen, 0.5));
	cmd->AddSequential(new HotGoalWait());
	cmd->AddSequential(new SLatch(Shooter::kUnlatched));
	cmd->AddSequential(new WaitCommand(1.5));

	cmd->AddParallel(new AngelChange(0));
	cmd->AddParallel(new DrawShooter());
	return cmd;
}
