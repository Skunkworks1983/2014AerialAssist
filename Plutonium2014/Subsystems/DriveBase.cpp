#include "DriveBase.h"
#include "../Robotmap.h"

#include "WPILib.h"
#include "../CommandBase.h"
#include "../Utils/SolenoidPair.h"
#include "../Commands/DriveBase/TankDrive.h"

DriveBase::DriveBase() : Subsystem("DriveBase") {
	motorLeftFront = new DRIVE_MOTOR_TYPE(1);
	motorRightFront = new DRIVE_MOTOR_TYPE(2);
	motorLeftBack = new DRIVE_MOTOR_TYPE(3);
	motorRightBack = new DRIVE_MOTOR_TYPE(4);
	encoderLeft = new Encoder(DRIVE_ENCODER_LEFT, false, Encoder::k4X);
	encoderRight = new Encoder(DRIVE_ENCODER_RIGHT, true, Encoder::k4X);
	shifter = new SolenoidPair(DRIVE_SHIFT_HIGH, DRIVE_SHIFT_LOW);
}

void DriveBase::InitDefaultCommand() {
	SetDefaultCommand(new TankDrive);
}


void DriveBase::setSpeed(double speedLeft, double speedRight){
	motorLeftFront->Set(-speedLeft);
	motorRightFront->Set(speedRight);
	motorLeftBack->Set(-speedLeft);
	motorRightBack->Set(speedRight);
}

float DriveBase::getMotorSpeed(){
	return (motorLeftFront->Get() +
			motorRightFront->Get()+
			motorLeftBack->Get() + 
			motorRightBack->Get()) / 4;
}

void DriveBase::encoderReset() {
	encoderLeft->Reset();
	encoderRight->Reset();
}

Encoder *DriveBase::getLeftEncoder(){
	return encoderLeft;
}

Encoder *DriveBase::getRightEncoder(){
	return encoderRight;
}

void DriveBase::setDriveGear(DriveGear gear){
	shifter->Set(gear==kHigh);
}

DriveBase::DriveGear DriveBase::getDriveGear() {
	return shifter->Get()?kHigh:kLow;
}

Gyro *DriveBase::getGyro(){
	return gyro;
}

