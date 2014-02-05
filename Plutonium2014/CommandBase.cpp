#include "CommandBase.h"
#include "Subsystems/Collector.h"
#include "Subsystems/DriveBase.h"
#include "Subsystems/Pterodactyl.h"
#include "Subsystems/Shootah.h"
#include "Subsystems/Pneumatics.h"
#include "Commands/Scheduler.h"

CommandBase::CommandBase(const char *name) : Command(name) {
}

CommandBase::CommandBase() : Command() {
}

// Initialize a single static instance of all of your subsystems to NULL
Collector* CommandBase::collector = NULL;
DriveBase* CommandBase::driveBase = NULL;
Pterodactyl* CommandBase::pterodactyl = NULL;

Shootah* CommandBase::shootah = NULL;
Pneumatics* CommandBase::pneumatics = NULL;
OI* CommandBase::oi = NULL;

void CommandBase::init() {
    // Create a single static instance of all of your subsystems. The following
	// line should be repeated for each subsystem in the project.
	collector = new Collector();
	//driveBase = new DriveBase();
	pterodactyl = new Pterodactyl();
	//shootah = new Shootah();
	//pneumatics = new Pneumatics();
	oi = new OI();
}

char *CommandBase::createNameFromFloat(char *base, float target) {
        char *buf = new char[32];
        snprintf(buf, 32, "%s_%f", base, target);
        return buf;
}

char *CommandBase::createNameFromString(char *base, const char *arg) {
        char *buf = new char[32];
        snprintf(buf, 32, "%s_%s", base, arg);
        return buf;
}
