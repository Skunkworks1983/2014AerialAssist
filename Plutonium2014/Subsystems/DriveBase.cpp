#include "DriveBase.h"
#include "../Robotmap.h"

#include "WPILib.h"
#include "../CommandBase.h"
#include "../Utils/SolenoidPair.h"
#include "../Commands/DriveBase/TankDrive.h"

DriveBase::DriveBase() :
	Subsystem("DriveBase") {
	motorLeftFront = new DRIVE_MOTOR_TYPE(DRIVE_MOTOR_FRONT_LEFT);
	motorRightFront = new DRIVE_MOTOR_TYPE(DRIVE_MOTOR_FRONT_RIGHT);
	motorLeftBack = new DRIVE_MOTOR_TYPE(DRIVE_MOTOR_BACK_LEFT);
	motorRightBack = new DRIVE_MOTOR_TYPE(DRIVE_MOTOR_BACK_RIGHT);
	// TODO Add to livewindow

	encoderLeft = new Encoder(DRIVE_ENCODER_LEFT, false, Encoder::k4X);
	LiveWindow::GetInstance()->AddSensor("Drive Base", "Encoder", encoderLeft);
	encoderLeft->Start();
	
	encoderRight = new Encoder(DRIVE_ENCODER_RIGHT, true, Encoder::k4X);
	LiveWindow::GetInstance()->AddSensor("Drive Base", "Encoder", encoderRight);
	encoderRight->Start();
	
	shifter = new SolenoidPair(DRIVE_SHIFT_HIGH, DRIVE_SHIFT_LOW);
	LiveWindow::GetInstance()->AddActuator("Drive Base", "Shifter", shifter);
}

void DriveBase::InitDefaultCommand() {
	SetDefaultCommand(new TankDrive);
}

void DriveBase::setSpeed(double speedLeft, double speedRight) {
	/*
	 * motorLeftFront->Set(-speedLeft);
	 * motorRightFront->Set(speedRight);
	 motorLeftBack->Set(-speedLeft);
	 motorRightBack->Set(speedRight);
	 */
}

float DriveBase::getMotorSpeed() {
	return (motorLeftFront->Get() + motorRightFront->Get()
			+ motorLeftBack->Get() + motorRightBack->Get()) / 4;
}

void DriveBase::encoderReset() {
	encoderLeft->Reset();
	encoderRight->Reset();
}

Encoder *DriveBase::getLeftEncoder() {
	return encoderLeft;
}

Encoder *DriveBase::getRightEncoder() {
	return encoderRight;
}

void DriveBase::setDriveGear(DriveGear gear) {
	//shifter->Set(gear);
}

DriveBase::DriveGear DriveBase::getDriveGear() {
	//return DriveBase::DriveGear shifter->Get();
	DriveBase::DriveGear foo;
	return foo;
}

Gyro *DriveBase::getGyro() {
	return gyro;
}

