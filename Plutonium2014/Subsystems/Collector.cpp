#include "Collector.h"
#include "../Robotmap.h"
#include "../Utils/Actuators/SolenoidPair.h"
#include "WPILib.h"
#include "../Utils/Actuators/StallableMotor.h"
#include "../Utils/Actuators/DualLiveSpeed.h"

Collector::Collector() :
	Subsystem("Collector") {

	rollerClawEncoder = new Encoder( COLLECTOR_CLAW_ENCODER_CHANNEL_A ,
	COLLECTOR_CLAW_ENCODER_CHANNEL_B, true, Encoder::k4X);
	rollerClawEncoder->SetPIDSourceParameter(Encoder::kRate);
	rollerClawEncoder->SetDistancePerPulse(1.0
			/COLLECTOR_ROLLER_TICKS_PER_ROTATION*60.0/COLLECTOR_ROLLER_MAX_RPM);
	rollerClawEncoder->Start();
	LiveWindow::GetInstance()->AddSensor("Collector", "Roller Encoder", rollerClawEncoder);
	
	DualLiveSpeed *motors = new DualLiveSpeed(new Talon(COLLECTOR_ROLLER_MOTOR_LEFT), new Talon(COLLECTOR_ROLLER_MOTOR_RIGHT), true);
	rollerMotor
			= (new StallableMotor(motors,COLLECTOR_ROLLER_STALL_SPEED))->setEncoderSource(rollerClawEncoder);
	
	rollerPIDController= new PIDController(1, .1, .01, rollerClawEncoder,
			rollerMotor, 0.05f);
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

void Collector::setJawState(Collector::JawState state) {
	jawController->Set(state);
}

Collector::JawState Collector::getJawState() {
	return (Collector::JawState) !jawState->Get();
}

void Collector::setRollerSpeed(float speed) {
	rollerPIDController->SetSetpoint(speed / COLLECTOR_ROLLER_MAX_RPM);

	if (speed != 0 && !rollerPIDController->IsEnabled()) {
		rollerPIDController->Enable();
	} else if (speed == 0) {
		if (rollerPIDController->IsEnabled()) {
			rollerPIDController->Disable();
		}
		rollerMotor->Set(0);
	}
}

double Collector::getDiff() {
	return rollerPIDController->GetSetpoint() - rollerClawEncoder->GetRate();
}

double Collector::getRollerSpeed() {
	SmartDashboard::PutBoolean("RollerStalled", rollerMotor->isStalled());
	return rollerClawEncoder->GetRate();
}

double Collector::getRollerDistance() {
	return rollerClawEncoder->GetDistance();
}

bool Collector::isBallDetected() {
	return !ballSensor->Get();
}
