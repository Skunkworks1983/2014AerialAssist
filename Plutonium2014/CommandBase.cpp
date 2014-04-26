#include "CommandBase.h"
#include "Subsystems/Collector.h"
#include "Subsystems/DriveBase.h"
#include "Subsystems/Pterodactyl.h"
#include "Subsystems/Shooter.h"
#include "Subsystems/Pneumatics.h"
#include "Subsystems/BeagleBone.h"
#include "Commands/Scheduler.h"
#include "Utils/Network/Server1180.h"

CommandBase::CommandBase(const char *name) :
	Command(name) {
}

CommandBase::CommandBase() :
	Command() {
}

// Initialize a single static instance of all of your subsystems to NULL
Collector* CommandBase::collector= NULL;
DriveBase* CommandBase::driveBase= NULL;
Pterodactyl* CommandBase::pterodactyl= NULL;

Shooter* CommandBase::shooter= NULL;
Pneumatics* CommandBase::pneumatics= NULL;
OI* CommandBase::oi= NULL;

BeagleBone* CommandBase::beaglebone= NULL;
Server1180* CommandBase::cheesy= NULL;
bool CommandBase::hot = false;

void CommandBase::init() {
	// Create a single static instance of all of your subsystems. The following
	// line should be repeated for each subsystem in the project.
	collector = new Collector();
	driveBase = new DriveBase();
	pterodactyl = new Pterodactyl();
	shooter = new Shooter();
	pneumatics = new Pneumatics();
	oi = new OI();
	beaglebone = new BeagleBone();
	cheesy = new Server1180(CommandBase::procPacket, NULL, false);
}

void CommandBase::procPacket(void *obj, char *pack) {
	hot= (strcmp(pack, "left")==0 || strcmp(pack, "right")==0 || strcmp(pack,
			"both")==0);
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
