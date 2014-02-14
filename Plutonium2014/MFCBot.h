#ifndef __MFC_BOT_H
#define __MFC_BOT_H

#include "WPILib.h"
#include "Commands/Command.h"
#include "CommandBase.h"

class MFCBot: public IterativeRobot {
private:
	int dont;
	
public:
	MFCBot();
	
	~MFCBot();
	virtual void RobotInit();
	virtual void AutonomousInit();
	virtual void AutonomousPeriodic();
	virtual void TeleopInit();
	virtual void TeleopPeriodic();
	virtual void TestPeriodic();
	void WatchDog();
private:
	LiveWindow *lw;
};

#endif
