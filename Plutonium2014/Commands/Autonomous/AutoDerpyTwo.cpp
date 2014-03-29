// Commands
#include "Autonomous.h"
#include "../Collector/Collect.h"
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

CommandGroup *Autonomous::createAutoArm() {
	CommandGroup *fireTheShotA = new CommandGroup("FireDaShot");
	fireTheShotA->AddSequential(new DiscBrake(Pterodactyl::kActive));
	fireTheShotA->AddSequential(new WLatch(Shooter::kLatched));
	fireTheShotA->AddSequential(new JawMove(Collector::kOpen, 0.5));
	fireTheShotA->AddSequential(new SLatch(Shooter::kUnlatched));
	fireTheShotA->AddSequential(new WaitCommand(1.5));
	return fireTheShotA;
}

Autonomous *Autonomous::createDerpyTwo() {
	CommandGroup *prepareA = new CommandGroup("prepareA");
	prepareA->AddParallel(new PrepareShooter(1.0));
	prepareA->AddSequential(new AngelChange(85.0,3));

	CommandGroup *collect = new CommandGroup("Collect");
	collect->AddSequential(new Collect());
	collect->AddSequential(new AngelChange(NEAR_SHOT_ANGLE));

	CommandGroup *collectAndDrive = new CommandGroup("CollectDrive");
	collectAndDrive->AddParallel(new PrepareShooter(NEAR_SHOT_POWER));
	collectAndDrive->AddSequential(new AngelChange(0));
	collectAndDrive->AddParallel(collect);
	collectAndDrive->AddSequential(new WaitCommand(0.5));
	collectAndDrive->AddSequential(new AutoStupidDrive(1.75, -.375));

	Autonomous *cmd = new Autonomous("DerpyTwo");
	cmd->AddSequential(prepareA);
	cmd->AddSequential(createAutoArm());

	cmd->AddSequential(new AutoStupidDrive(0.25, .375));
	
	cmd->AddSequential(collectAndDrive);
	cmd->AddSequential(createAutoArm());

	cmd->AddParallel(new AngelChange(0));
	cmd->AddParallel(new DrawShooter());
	return cmd;
}
