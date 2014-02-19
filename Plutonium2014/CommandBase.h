#ifndef COMMAND_BASE_H
#define COMMAND_BASE_H

#include "Commands/Command.h"
#include "Subsystems/Collector.h"
#include "Subsystems/DriveBase.h"
#include "Subsystems/Pterodactyl.h"
#include "Subsystems/Shooter.h"
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
	static Shooter *shooter;
	static Pneumatics *pneumatics;
	static OI *oi;
	
	static char *createNameFromString(char *base, const char *arg);
	static char *createNameFromFloat(char *base, float target);
};

#endif
