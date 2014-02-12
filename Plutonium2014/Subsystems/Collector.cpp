#include "Collector.h"
#include "../Robotmap.h"
#include "../Utils/SolenoidPair.h"
#include "WPILib.h"

Collector::Collector() :
	Subsystem("Collector") {

	rollerMotorLeft = new Victor(COLLECTOR_ROLLER_MOTOR_LEFT);
	rollerClawEncoderLeft = new Encoder(COLLECTOR_CLAW_ENCODER_CHANNEL_A,
			COLLECTOR_CLAW_ENCODER_CHANNEL_B, true, Encoder::k4X);

	rollerClawEncoderLeft->SetPIDSourceParameter(Encoder::kRate);
	rollerClawEncoderLeft->SetDistancePerPulse(
			COLLECTOR_ROLLER_300_ROTATIONS_PER_TICK);
	rollerClawEncoderLeft->Start();

	rollerPIDControllerLeft = new PIDController(1, .1, .01, rollerClawEncoderLeft,
			rollerMotorLeft, 0.05f);
	rollerPIDControllerLeft->SetInputRange(-2.0, 2.0);
	rollerPIDControllerLeft->SetOutputRange(-1.0, 1.0);
	
	
	rollerMotorRight = new Victor(COLLECTOR_ROLLER_MOTOR_RIGHT);
	rollerClawEncoderRight = new Encoder(COLLECTOR_CLAW_ENCODER_CHANNEL_A,
			COLLECTOR_CLAW_ENCODER_CHANNEL_B, true, Encoder::k4X);

	rollerClawEncoderRight->SetPIDSourceParameter(Encoder::kRate);
	rollerClawEncoderRight->SetDistancePerPulse(
			COLLECTOR_ROLLER_300_ROTATIONS_PER_TICK);
	rollerClawEncoderRight->Start();

	rollerPIDControllerRight = new PIDController(1, .1, .01, rollerClawEncoderRight,
			rollerMotorRight, 0.05f);
	rollerPIDControllerRight->SetInputRange(-2.0, 2.0);
	rollerPIDControllerRight->SetOutputRange(-1.0, 1.0);

	//SmartDashboard::PutData("Roller PID", rollerPIDController);
	ballSensor = new DigitalInput(COLLECTOR_BALL_SENSOR);
	jawController = new SolenoidPair(COLLECTOR_JAW_SOLENOID_A,
			COLLECTOR_JAW_SOLENOID_B);
	jawState = new DigitalInput(COLLECTOR_JAW_STATE);
}

void Collector::InitDefaultCommand() {
	// Nothing here...
}

void Collector::setJawState(bool on) {
	jawController->Set(on);
}

bool Collector::getJawState() {
	return jawState->Get();
}

void Collector::setRollerSpeedLeft(float speed) {
	rollerPIDControllerLeft->SetSetpoint(speed);

	if (speed != 0 && !rollerPIDControllerLeft->IsEnabled()) {
		rollerPIDControllerLeft->Enable();
	} else if (speed == 0) {
		if (rollerPIDControllerLeft->IsEnabled()) {
			rollerPIDControllerLeft->Disable();
		}
		rollerMotorLeft->Set(0);
	}
}

double Collector::getDiffLeft() {
	return rollerPIDControllerLeft->GetSetpoint() - rollerClawEncoderLeft->GetRate();
}

double Collector::getRollerSpeedLeft() {
	return rollerClawEncoderLeft->GetRate();
}

double Collector::getRollerDistanceLeft() {
	return rollerClawEncoderLeft->GetDistance();
}

void Collector::setRollerSpeedRight(float speed) { //This is the right things
	rollerPIDControllerRight->SetSetpoint(speed);

	if (speed != 0 && !rollerPIDControllerRight->IsEnabled()) {
		rollerPIDControllerRight->Enable();
	} else if (speed == 0) {
		if (rollerPIDControllerRight->IsEnabled()) {
			rollerPIDControllerRight->Disable();
		}
		rollerMotorLeft->Set(0);
	}
}

double Collector::getDiffRight() {
	return rollerPIDControllerRight->GetSetpoint() - rollerClawEncoderRight->GetRate();
}

double Collector::getRollerSpeedRight() {
	return rollerClawEncoderRight->GetRate();
}

double Collector::getRollerDistanceRight() {
	return rollerClawEncoderRight->GetDistance();
}

bool Collector::isBallDetected() {
	return !ballSensor->Get();
}
