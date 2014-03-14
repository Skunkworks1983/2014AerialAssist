#ifndef AUTO_STUPID_DRIVE_CPP
#define AUTO_STUPID_DRIVE_CPP

// Backend
#include "../../CommandBase.h"
#include "WPILib.h"

class AutoStupidDrive : public CommandBase {
private:
	float speed;
public:
	AutoStupidDrive(double timeout, float speed);
	virtual void Initialize();
	virtual void Execute();
	virtual bool IsFinished();
	virtual void End();
	virtual void Interrupted();
};
#endif
