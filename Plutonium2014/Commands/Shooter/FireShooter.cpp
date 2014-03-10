#include "FireShooter.h"
#include "../../Subsystems/Shooter.h"
#include "../../Robotmap.h"
#include "../Collector/JawMove.h"
#include "../../Utils/Commands/CommandStarter.h"
#include "Raw/FireShooterInternal.h"

#include "Latches/SLatch.h"
#include "Latches/WLatch.h"

FireShooter::FireShooter() :
	CommandBase("FireShooter") {
}

void FireShooter::Initialize() {
	if ((CommandBase::pterodactyl->isPIDFinished()
			|| CommandBase::pterodactyl->getPIDTarget() > 45)
			&& CommandBase::pterodactyl->getAngle() > 45) {
		Scheduler::GetInstance()->AddCommand(new FireShooterInternal());
	} else {
		Logger::log(Logger::kInfo, "Shooter-FireShooter", "Ignoring fire shooter due to pterodactyl angle!");
	}
}

void FireShooter::Execute() {
}

bool FireShooter::IsFinished() {
	return true;
}

void FireShooter::End() {
}

void FireShooter::Interrupted() {
}
