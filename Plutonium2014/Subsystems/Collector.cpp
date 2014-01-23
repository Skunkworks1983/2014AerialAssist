#include "Collector.h"
#include "../Robotmap.h"
#include "../Utils/SolenoidPair.h"
#include "WPILib.h"

Collector::Collector() :
	Subsystem("Collector") {
	
	rollerClawMotor = new Talon(COLLECTOR_ROLLER_MOTOR);
	rollerClawEncoder = new Encoder(COLLECTOR_CLAW_ENCODER_CHANNEL_A, COLLECTOR_CLAW_ENCODER_CHANNEL_B, true, Encoder::k4X);
	
	rollerPIDController = new PIDController(0,0,0, rollerClawEncoder, rollerClawMotor, 0.1f);
	
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

double Collector::getRollerSpeed(){
	return rollerClawEncoder->Get();
}

bool Collector::isBallDetected(){
	return ballSensor->Get();
}

