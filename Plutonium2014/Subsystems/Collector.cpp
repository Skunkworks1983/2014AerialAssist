#include "Collector.h"
#include "../Robotmap.h"
#include "WPILib.h"

Collector::Collector() :
	Subsystem("Collector") {
	bangBangLeft = new PIDController(0,0,0, mouthEncoderLeft, mouthMotorLeft, 0.1f);
	bangBangRight = new PIDController(0,0,0, mouthEncoderRight, mouthMotorRight, 0.1f);
	rollerMotorLeft = new Talon(9);
	rollerMotorRight = new Talon(10);
	mouthMotorLeft = new Talon(11);
	mouthMotorRight = new Talon(12);
	mouthEncoderLeft = new Encoder(1, 2, false, Encoder::k4X);
	mouthEncoderRight = new Encoder(1, 2, true, Encoder::k4X);
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
	rollerMotorLeft->Set(speed);
	rollerMotorRight->Set(speed);
}

double Collector::getMouthPositionLeft() { //Will not work (probably?) but just placeholder
	return bangBangLeft->Get();
}

double Collector::getMouthPositionRight() { //Will not work (probably?) but just placeholder
	return bangBangRight->Get();
}

double Collector::getMouthEncoderLeft() {
	return mouthEncoderLeft->Get();
}

double Collector::getMouthEncoderRight() {
	return mouthEncoderRight->Get();
}

