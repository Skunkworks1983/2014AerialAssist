#ifndef AUTO_STUPID_DRIVE_CPP
#define AUTO_STUPID_DRIVE_CPP

// Backend
#include "../../CommandBase.h"

class AutoStupidDrive : public CommandBase {
public:
	AutoStupidDrive(double timeout) {
		Requires(driveBase);
		SetTimeout(timeout);
	}
	virtual void Initialize() {
	}
	virtual void Execute() {
		driveBase->setSpeed(0.25, 0.25);
	}
	virtual bool IsFinished() {
		return IsTimedOut();
	}
	virtual void End() {
		driveBase->setSpeed(0, 0);
	}
	virtual void Interrupted() {
		driveBase->setSpeed(0, 0);
	}
};

#endif
