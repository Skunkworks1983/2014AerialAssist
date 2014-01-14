#include "DriveBase.h"
#include "../Robotmap.h"

#include "WPILib.h"
#include "../CommandBase.h"
#include "../Utils/SolenoidPair.h"
#include "../Commands/DriveBase/TankDrive.h"

DriveBase::DriveBase() : Subsystem("DriveBase") {
	motorLeftFront = new Jaguar(1);
	motorRightFront = new Jaguar(2);
	motorLeftBack = new Jaguar(3);
	motorRightBack = new Jaguar(4);
	encoderLeftFront = new Encoder(1, 1);
	encoderRightFront = new Encoder(2, 2);
	encoderLeftBack = new Encoder(3, 3);
	encoderRightBack = new Encoder(4, 4);
	shifter = new SolenoidPair(1, 2);
}

void DriveBase::InitDefaultCommand() {
	SetDefaultCommand(new TankDrive);
}

void DriveBase::setSpeed(double speedLeft, double speedRight){
	motorLeftFront->Set(speedLeft);
	motorRightFront->Set(speedRight);
	motorLeftBack->Set(speedLeft);
	motorRightBack->Set(speedRight);
}

void DriveBase::setDriveGear(DriveGear gear){
	shifter->Set(gear==kHigh);
}

DriveBase::DriveGear DriveBase::getDriveGear() {
	return shifter->Get()?kHigh:kLow;
}

// Put methods for controlling this subsystem
// here. Call these from Commands.

