#include "Pterodactyl.h"
#include "../Robotmap.h"
#define PTERODACTYL_POT 5
#define PTERODACTYL_MAX_ANGLE 90
#define PTERODACTYL_MIN_ANGLE 0
#define THRESHOLD_LOWER 10
#define THRESHOLD_UPPER 10
#define LIL_BIT 0.5

Pterodactyl::Pterodactyl() : Subsystem("Pterodactyl") {
	motorLeft = new Talon(1);
	motorRight = new Talon(2);
	encoderLeft = new Encoder(DRIVE_ENCODER_LEFT, false, Encoder::k4X);
	encoderRight = new Encoder(DRIVE_ENCODER_RIGHT, true, Encoder::k4X); //Copied from drivebase. I don't even know
	pot = new AnalogChannel(PTERODACTYL_POT);
}
    
void Pterodactyl::InitDefaultCommand() {

}

double Pterodactyl::getAngle(){
	return ((90*pot->GetAverageVoltage())-50);
}

void Pterodactyl::setAngleMotorSpeed(float speed){
	if((speed>0 && getAngle()<PTERODACTYL_MAX_ANGLE) || (speed<0 && getAngle()>PTERODACTYL_MIN_ANGLE)){
		motorLeft->Set(speed);
		motorRight->Set(-speed);
	}
}

void Pterodactyl::setAngle(float target){
	if(getAngle() < (target+LIL_BIT)){ //within half a degree so the pterodactyl doesn't swing indefinately
		setAngleMotorSpeed(1);
	}
	else if(getAngle() > (target-LIL_BIT)){
		setAngleMotorSpeed(-1);
	}
	if(getAngle()<(target+THRESHOLD_LOWER) && (target-LIL_BIT) < getAngle()){ //if the current angle is past the lower threshold and going down
		setAngleMotorSpeed(-0.5);
	}
	else if(getAngle()>(target-THRESHOLD_UPPER) && (target+LIL_BIT) > getAngle()){
		setAngleMotorSpeed(0.5);
	}
	if(getAngle() < (target+LIL_BIT) && getAngle() > (target-LIL_BIT)){ //checks if current angle is near target and stops
		setAngleMotorSpeed(0);
	}
}
