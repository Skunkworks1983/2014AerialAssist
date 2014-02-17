#include "Collector.h"
#include "../Robotmap.h"
#include "../Utils/Actuators/SolenoidPair.h"
#include "WPILib.h"
#include "../Utils/Actuators/StallableMotor.h"

Collector::Collector() :
	Subsystem("Collector") {

	rollerClawEncoder = new Encoder( COLLECTOR_CLAW_ENCODER_CHANNEL_A ,
			COLLECTOR_CLAW_ENCODER_CHANNEL_B, true, Encoder::k4X);
	rollerClawEncoder->SetPIDSourceParameter(Encoder::kRate);
	rollerClawEncoder->SetDistancePerPulse(1.0
			/COLLECTOR_ROLLER_TICKS_PER_ROTATION*60.0/COLLECTOR_ROLLER_MAX_RPM);
	rollerClawEncoder->Start();
	LiveWindow::GetInstance()->AddSensor("Collector", "Roller Encoder", rollerClawEncoder);

	rollerMotorLeft
			= (new StallableMotor(new Talon(COLLECTOR_ROLLER_MOTOR_LEFT),0))->setEncoderSource(rollerClawEncoder);
	rollerMotorRight
			= (new StallableMotor(new Talon(COLLECTOR_ROLLER_MOTOR_RIGHT),0))->setEncoderSource(rollerClawEncoder);

	rollerPIDController= new PIDController(1, .1, .01, rollerClawEncoder,
			this, 0.05f);
	rollerPIDController->SetInputRange(-2.0, 2.0);
	rollerPIDController->SetOutputRange(-1.0, 1.0);
	LiveWindow::GetInstance()->AddActuator("Collector", "PID Controller", rollerPIDController);
	SmartDashboard::PutData("collectorPID", rollerPIDController);

	ballSensor = new DigitalInput(COLLECTOR_BALL_SENSOR);
	LiveWindow::GetInstance()->AddSensor("Collector", "Ball Sensor", ballSensor);

	jawController = new SolenoidPair(COLLECTOR_JAW_SOLENOID_A,
			COLLECTOR_JAW_SOLENOID_B);
	LiveWindow::GetInstance()->AddActuator("Collector", "Jaw Controller", jawController);

	jawState = new DigitalInput(COLLECTOR_JAW_STATE);
	LiveWindow::GetInstance()->AddSensor("Collector", "Jaw State", jawState);
}

void Collector::InitDefaultCommand() {
	// Nothing here...
}

void Collector::setJawState(bool closed) {
	jawController->Set(closed);
}

bool Collector::getJawState() {
	return jawState->Get();
}

void Collector::setRollerSpeed(float speed) {
	rollerPIDController->SetSetpoint(speed / COLLECTOR_ROLLER_MAX_RPM);

	if (speed != 0 && !rollerPIDController->IsEnabled()) {
		rollerPIDController->Enable();
	} else if (speed == 0) {
		if (rollerPIDController->IsEnabled()) {
			rollerPIDController->Disable();
		}
		rollerMotorLeft->Set(0);
		rollerMotorRight->Set(0);
	}
}

void Collector::PIDWrite(float speed) {
	rollerMotorLeft->Set(speed);
	rollerMotorRight->Set(-speed);
}

double Collector::getDiff() {
	return rollerPIDController->GetSetpoint() - rollerClawEncoder->GetRate();
}

double Collector::getRollerSpeed() {
	SmartDashboard::PutBoolean("RollerStalled", rollerClawEncoder->GetStopped());
	return rollerClawEncoder->GetRate();
}

double Collector::getRollerDistance() {
	return rollerClawEncoder->GetDistance();
}

bool Collector::isBallDetected() {
	return !ballSensor->Get();
}
