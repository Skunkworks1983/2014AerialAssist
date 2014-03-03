#ifndef __CMD_AUTONOMOUS_H
#define __CMD_AUTONOMOUS_H

#include "WPILib.h"

class Autonomous: public CommandGroup {
public:
	static Autonomous *create1Ball(float distance);
	static Autonomous *create2Ball(float distance);
	static Autonomous *createAutoBall(int ballCount, float distance);
	static Autonomous *createJustDrive(float distance);
public:
	Autonomous();
	Autonomous(char *style);
	virtual void Initialize();
	~Autonomous();
};

#endif
