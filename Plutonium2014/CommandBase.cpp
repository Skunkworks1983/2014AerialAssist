#include "CommandBase.h"
#include "Subsystems/Collector.h"
#include "Subsystems/DriveBase.h"
#include "Subsystems/Pterodactyl.h"
#include "Subsystems/Shootah.h"
#include "Commands/Scheduler.h"

CommandBase::CommandBase(const char *name) : Command(name) {
}

CommandBase::CommandBase() : Command() {
}

// Initialize a single static instance of all of your subsystems to NULL
Collector* collector = NULL;
DriveBase* driveBase = NULL;
Pterodactyl* pterodactyl = NULL;
Shootah* shootah = NULL;
OI* CommandBase::oi = NULL;

void CommandBase::init() {
    // Create a single static instance of all of your subsystems. The following
	// line should be repeated for each subsystem in the project.
	collector = new Collector();
	driveBase = new DriveBase();
	pterodactyl = new Pterodactyl();
	shootah = new Shootah();
	oi = new OI();
}
