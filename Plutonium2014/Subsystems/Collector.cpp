#include "Collector.h"
#include "../Robotmap.h"
#include "WPILib.h"

Collector::Collector() :
	Subsystem("Collector") {
	bangBangLeft = new PIDController(0,0,0, mouthEncoderLeft, mouthMotorLeft, 0.1f);
	rollerClawController = new PIDController(0,0,0, rollerClawEncoder, mouthMotorRight, 0.1f);
	rollerClawMotor = new Talon(9);
	mouthMotorLeft = new Talon(10);
	mouthMotorRight = new Talon(11);
	mouthEncoderLeft = new Encoder(1, 2, false, Encoder::k4X);
	rollerClawEncoder = new Encoder(1, 2, true, Encoder::k4X);
}

void Collector::setMouthSpeed(float speed){
	mouthMotorLeft->Set(speed);
	mouthMotorRight->Set(speed);
}

void Collector::InitDefaultCommand() {
	// Nothing here...
}

/*void Collector::setArmPosition(Position defaultPos) {

 }*/

void Collector::setRollerSpeed(float speed) {
	rollerClawMotor->Set(speed);
	
}

double Collector::getMouthPositionLeft() { //Will not work (probably?) but just placeholder
	return bangBangLeft->Get();
}

double Collector::getMouthPositionRight() { //Will not work (probably?) but just placeholder
	return rollerClawController->Get();
}

double Collector::getRollerClawEncoder() {
	return rollerClawEncoder->Get();
}

