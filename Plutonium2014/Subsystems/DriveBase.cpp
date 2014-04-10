#include "DriveBase.h"
#include "../Robotmap.h"

#include "WPILib.h"
#include "../CommandBase.h"
#include "../Utils/Actuators/SolenoidPair.h"
#include "../Utils/Actuators/DualLiveSpeed.h"
#include "../Commands/DriveBase/TankDrive.h"

DriveBase::DriveBase() :
	Subsystem("DriveBase") {
	motorLeft = new DualLiveSpeed(new DRIVE_MOTOR_TYPE(DRIVE_MOTOR_FRONT_LEFT),
			new DRIVE_MOTOR_TYPE(DRIVE_MOTOR_BACK_LEFT), false);
	LiveWindow::GetInstance()->AddActuator("Drive Base", "Motor Left", motorLeft);
	motorRight = new DualLiveSpeed(
			new DRIVE_MOTOR_TYPE(DRIVE_MOTOR_FRONT_RIGHT),
			new DRIVE_MOTOR_TYPE(DRIVE_MOTOR_BACK_RIGHT), false);
	LiveWindow::GetInstance()->AddActuator("Drive Base", "Motor Right", motorRight);

	encoderLeft = new Encoder(DRIVE_ENCODER_LEFT, false, Encoder::k4X);
	LiveWindow::GetInstance()->AddSensor("Drive Base", "EncoderLeft", encoderLeft);
	encoderLeft->Start();
	encoderLeft->Reset();

	encoderRight = new Encoder(DRIVE_ENCODER_RIGHT, true, Encoder::k4X);
	LiveWindow::GetInstance()->AddSensor("Drive Base", "EncoderRight", encoderRight);
	encoderRight->Start();
	encoderRight->Reset();

	shifter = new SolenoidPair(DRIVE_SHIFT_HIGH, DRIVE_SHIFT_LOW);
	LiveWindow::GetInstance()->AddActuator("Drive Base", "Shifter", shifter);

	setDriveGear(DriveBase::kHigh);
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
	if (gear != shifter->Get()) {
		encoderReset();
	}
	shifter->Set(gear);
	// Adjust encoder distance per tick
	double distancePerTick = 1.0;
	if (gear == DriveBase::kHigh) {
		distancePerTick = 4.0 * 3.141592 / 645.0;
	} else {
		distancePerTick = 4.0 * 3.141592 / (645.0 * 10.549 / 3.610);
	}
	encoderLeft->SetDistancePerPulse(distancePerTick);
	encoderRight->SetDistancePerPulse(distancePerTick);
}

DriveBase::DriveGear DriveBase::getDriveGear() {
	return shifter->Get() ? DriveBase::kHigh : DriveBase::kLow;
}
