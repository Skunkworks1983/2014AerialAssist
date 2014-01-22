#include "Shootah.h"
#include "../Robotmap.h"
#include "WPILib.h"

Shootah::Shootah() :
	Subsystem("Shootah") {
	winchMotor = new Victor(SHOOTAH_MOTOR_WINCH);
	winchEncoder = new Encoder(SHOOTAH_ENCODER_WINCH, true, Encoder::k4X);
	
	winchPID = new PIDController(1, 1, 1, winchEncoder, winchMotor, 0.0f);
	
	pneumaticCoffeeTable = new Solenoid(SHOOTAH_PNEUMATIC_COFFEE_TABLE);
	pneumaticBloodyBogan = new Solenoid(SHOOTAH_PNEUMATIC_WANKER);
	
	pullbackSwitch = new DigitalInput(SHOOTAH_LIMITSWITCH_PULLBACK_CHECK);
	
	cachedPosition =  Shootah::kUnaligned;
}

void Shootah::InitDefaultCommand() {
	
}

void Shootah::setWinchMotorSpeed(float speed) {
	winchMotor->Set(speed);
}

double Shootah::getEncoder() {
	return winchEncoder->Get();
}

float Shootah::getWinchPID() {
	return winchPID->Get();
}

void Shootah::setWinchPID(bool enable) {
	// This will just enable all the PID things, will be doing later when other
	//     parts of the PID system are complete/are important to do.
}

void Shootah::setCoffeTable(bool state) {
	pneumaticCoffeeTable->Set(state); // TODO: Check if it is in a position that makes sense 
}

bool Shootah::getCoffeTable() { 
	return pneumaticCoffeeTable->Get();
}

void Shootah::setBloodyBogan(bool state) {
	if (pneumaticCoffeeTable->Get()) { // Saftey???
		pneumaticBloodyBogan->Set(state);
	}
}

bool Shootah::getBloodyBogan() {
	return pneumaticBloodyBogan->Get();
}

bool Shootah::pullbackDone() {
	if (cachedPosition != Shootah::kUnaligned || pullbackSwitch->Get()) {
		return pullbackSwitch->Get();
	}
	
	return false;
}
