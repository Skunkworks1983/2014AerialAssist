#include "Pterodactyl.h"
#include "../Robotmap.h"

Pterodactyl::Pterodactyl() : Subsystem("Pterodactyl") {
	motorLeft = new Talon(1);
	motorRight = new Talon(2);
	encoderLeft = new Encoder(DRIVE_ENCODER_LEFT, false, Encoder::k4X);
	encoderRight = new Encoder(DRIVE_ENCODER_LEFT, true, Encoder::k4X); //Copied from drivebase. I don't even know
}
    
void Pterodactyl::InitDefaultCommand() {
	// Set the default command for a subsystem here.
	//SetDefaultCommand(new MySpecialCommand());
}

// Put methods for controlling this subsystem
// here. Call these from Commands.

void Pterodactyl::setPitch(float direction){

}

float Pterodactyl::getPitch(){

}

void Pterodactyl::updatePIDOutput(){

}

double PIDGet(){

}
