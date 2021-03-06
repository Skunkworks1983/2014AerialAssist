#include "FireShooter.h"

// Utils
#include "../../Utils/Commands/CommandStarter.h"
#include "../../Utils/Logger.h"

// Backend
#include "../../Robotmap.h"

// Commands
#include "Raw/FireShooterInternal.h"

FireShooter::FireShooter() :
	CommandBase("FireShooter") {
}

void FireShooter::Initialize() {
	if (CommandBase::shooter->lastReleasePosition > 0.0
			&& (CommandBase::pterodactyl->isPIDFinished()
					|| CommandBase::pterodactyl->getPIDTarget() > 45)
			&& CommandBase::pterodactyl->getAngle() > 45) {
		Scheduler::GetInstance()->AddCommand(new FireShooterInternal());
	} else {
		if (CommandBase::shooter->lastReleasePosition > 0.0) {
			Logger::log(Logger::kInfo, "Shooter-FireShooter",
					"Ignoring fire shooter due to pterodactyl angle!");
		} else {
			Logger::log(Logger::kInfo, "Shooter-FireShooter",
					"Ignoring fire shooter due to unprepared!");
		}
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
