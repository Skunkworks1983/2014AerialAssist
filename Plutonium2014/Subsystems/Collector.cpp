#include "Collector.h"
#include "../Robotmap.h"
#include "../Utils/SolenoidPair.h"
#include "WPILib.h"

Collector::Collector() :
	Subsystem("Collector") {
	
	rollerMotor = new Victor(COLLECTOR_ROLLER_MOTOR);
	rollerClawEncoder = new Encoder(COLLECTOR_CLAW_ENCODER_CHANNEL_A, COLLECTOR_CLAW_ENCODER_CHANNEL_B, true, Encoder::k4X);
	
	rollerClawEncoder->SetPIDSourceParameter(Encoder::kRate);
	rollerClawEncoder->SetDistancePerPulse(COLLECTOR_ROLLER_300_ROTATIONS_PER_TICK);
	rollerClawEncoder->Start();
	
	rollerPIDController = new PIDController(1,.1,.01, rollerClawEncoder, rollerMotor, 0.05f);
	rollerPIDController->SetInputRange(-2.0,2.0);
	rollerPIDController->SetOutputRange(-1.0,1.0);
	
	//SmartDashboard::PutData("Roller PID", rollerPIDController);
	ballSensor = new DigitalInput(COLLECTOR_BALL_SENSOR);
	jawController = new SolenoidPair(COLLECTOR_JAW_SOLENOID_A, COLLECTOR_JAW_SOLENOID_B);
	jawState = new DigitalInput(COLLECTOR_JAW_STATE);
}

void Collector::InitDefaultCommand() {
	// Nothing here...
}

void Collector::setJawState(bool on){
	jawController->Set(on);
}

bool Collector::getJawState(){
	return jawState->Get();
}

void Collector::setRollerSpeed(float speed){
	rollerPIDController->SetSetpoint(speed);
	
	if(speed != 0 && !rollerPIDController->IsEnabled()){
		rollerPIDController->Enable();
	}else if(speed == 0 && rollerPIDController->IsEnabled()){
		rollerPIDController->Disable();
	}
}

double Collector::getDiff() {
	return rollerPIDController->GetSetpoint() - rollerClawEncoder->GetRate();
}

double Collector::getRollerSpeed(){
	return rollerClawEncoder->GetRate();
}

double Collector::getRollerDistance(){
	return rollerClawEncoder->GetDistance();
}

bool Collector::isBallDetected(){
	return ballSensor->Get();
}
