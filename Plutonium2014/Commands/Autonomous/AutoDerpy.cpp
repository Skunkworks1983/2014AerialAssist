// Commands
#include "Autonomous.h"
#include "../Pterodactyl/AngelChange.h"
#include "../Automatic/AutoDriveDistance.h"
#include "../Collector/JawMove.h"
#include "../Shooter/Raw/FireShooterInternal.h"
#include "../Shooter/DrawShooter.h"
#include "../Shooter/PrepareShooter.h"
#include "../Automatic/HotGoalWait.h"
#include "AutoStupidDrive.h"

Autonomous *Autonomous::createDerpy() {
	Autonomous *cmd = new Autonomous("Derpy");
	CommandGroup *prepare = new CommandGroup("CHILD");
	prepare->AddParallel(new PrepareShooter(SHOOTER_POWER_TURNS_3));
	prepare->AddSequential(new AngelChange(0));
	prepare->AddSequential(new AngelChange(88));
	cmd->AddSequential(prepare);
	
	// Fire Shooter Internal
	cmd->AddSequential(new DiscBrake(Pterodactyl::kActive));
	cmd->AddSequential(new WLatch(Shooter::kLatched));
	cmd->AddSequential(new JawMove(Collector::kOpen, 1.5));
	AddSequential(new SLatch(Shooter::kUnlatched));
	AddSequential(new WaitCommand(1.5));
	
	cmd->AddParallel(new AngelChange(0));
	cmd->AddParallel(new DrawShooter());
	cmd->AddSequential(new AutoStupidDrive(3.0,-.25)); //All of these magic number need to be less magic
	return cmd;
}
