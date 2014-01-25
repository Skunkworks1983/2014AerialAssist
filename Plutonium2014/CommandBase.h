#ifndef COMMAND_BASE_H
#define COMMAND_BASE_H

#include "Commands/Command.h"
#include "Subsystems/Collector.h"
#include "Subsystems/DriveBase.h"
#include "Subsystems/Pterodactyl.h"
#include "Subsystems/Shootah.h"
#include "Subsystems/Pneumatics.h"
#include "OI.h"


/**
 * The base for all commands. All atomic commands should subclass CommandBase.
 * CommandBase stores creates and stores each control system. To access a
 * subsystem elsewhere in your code in your code use CommandBase.examplesubsystem
 */
class CommandBase: public Command {
public:
	CommandBase(const char *name);
	CommandBase();
	static void init();
	// Create a single static instance of all of your subsystems
	static Collector *collector;
	static DriveBase *driveBase;
	static Pterodactyl *pterodactyl;
	static Shootah *shootah;
	static Pneumatics *pneumatics;
	static OI *oi;
	
	char *CommandBase::createNameFromString(char *base, const char *arg);
	char *CommandBase::createNameFromFloat(char *base, float target);
};

#endif
