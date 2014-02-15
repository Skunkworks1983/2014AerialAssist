#include "DriveBase.h"
#include "../Robotmap.h"

#include "WPILib.h"
#include "../CommandBase.h"
#include "../Utils/SolenoidPair.h"
#include "../Utils/DualLiveSpeed.h"
#include "../Commands/DriveBase/TankDrive.h"

DriveBase::DriveBase() :
	Subsystem("DriveBase") {
	motorLeft = new DualLiveSpeed(new DRIVE_MOTOR_TYPE(DRIVE_MOTOR_FRONT_LEFT),
			new DRIVE_MOTOR_TYPE(DRIVE_MOTOR_BACK_LEFT), false);
	LiveWindow::GetInstance()->AddActuator("Drive Base", "Motor Left",
			motorLeft);
	motorRight
			= new DualLiveSpeed(new DRIVE_MOTOR_TYPE(DRIVE_MOTOR_FRONT_RIGHT),
					new DRIVE_MOTOR_TYPE(DRIVE_MOTOR_BACK_RIGHT), false);
	LiveWindow::GetInstance()->AddActuator("Drive Base", "Motor Right",
			motorRight);
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
	motorLeft->Set(-speedLeft);
	motorRight->Set(speedRight);
}

float DriveBase::getMotorSpeed() {
	return (motorLeft->Get() + motorRight->Get()) / 2;
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
	shifter->Set(gear);
}

DriveBase::DriveGear DriveBase::getDriveGear() {
	return (DriveBase::DriveGear) shifter->Get();
}

Gyro *DriveBase::getGyro() {
	return gyro;
}

