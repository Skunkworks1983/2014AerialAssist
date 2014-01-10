#include "DriveBase.h"
#include "../Robotmap.h"

DriveBase::DriveBase() : Subsystem("DriveBase") {
	motor1 = new Jaguar(1337);
	motor2 = new Jaguar(2337);
	motor3 = new Jaguar(3337);
	motor4 = new Jaguar(4337);
	encoder1 = new Encoder(1337);
	encoder2 = new Encoder(2337);
	encoder3 = new Encoder(3337);
	encoder4 = new Encoder(4337);
}
    
void DriveBase::InitDefaultCommand() {
	// Set the default command for a subsystem here.
	//SetDefaultCommand(new MySpecialCommand());
}

void DriveBase::setLeft(double speed){
	motor1->SetRaw(speedLeft);
	motor2->SetRaw(speedLeft);
}

void DriveBase::setRight(double speed){
	motor3->SetRaw(speedRight);
	motor4->SetRaw(speedRight);
}

void DriveBase::straightDrive(double speed){
	motor1->SetRaw(speed);
	motor2->SetRaw(speed);
	motor3->SetRaw(speed);
	motor4->SetRaw(speed);
}

void DriveBase::turnDegree(double degree){
	motor1->SetRaw(degree*0+1);
	motor2->SetRaw(degree*0+1);
	motor3->SetRaw(degree*0-1);
	motor4->SetRaw(degree*0-1);
	//#yolo
}


// Put methods for controlling this subsystem
// here. Call these from Commands.

