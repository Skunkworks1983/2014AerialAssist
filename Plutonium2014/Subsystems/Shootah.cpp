#include "Shootah.h"
#include "../Robotmap.h"
#include "../Utils/SolenoidPair.h"
#include "WPILib.h"

Shootah::Shootah() :
	Subsystem("Shootah") {
	winchMotor = new Victor(SHOOTAH_MOTOR_WINCH);
	winchEncoder = new Encoder(SHOOTAH_ENCODER_WINCH, true, Encoder::k4X);

	winchPID = new PIDController(1, 0.5, 0.001, winchEncoder, winchMotor, 0.0f);

	pneumaticCoffeeTable = new SolenoidPair(SHOOTAH_PNEUMATIC_COFFEE_TABLE);
	pneumaticBloodyBogan = new SolenoidPair(SHOOTAH_PNEUMATIC_BLOODY_BOGAN);

	pullbackSwitch = new DigitalInput(SHOOTAH_LIMITSWITCH_PULLBACK_CHECK);

	//cachedPosition = Shootah::kUnaligned;
}

void Shootah::InitDefaultCommand() {

}

void Shootah::setWinchPID(float setpoint) {
	winchPID->Reset();
	winchPID->SetSetpoint(setpoint);
	if (setpoint != 0 && !winchPID->IsEnabled()) {
		winchPID->Enable();
	}
}

bool Shootah::isWinchPIDSetpoint() {
	return winchPID->Get() == winchPID->GetSetpoint();
}

double Shootah::getWinchEncoder() {
	if (winchEncoder->GetStopped()) {
		winchEncoder->Start();
		return winchEncoder->GetRaw();
	}
}

void Shootah::setWinchEncoderState(bool on) {
	if (winchEncoder->GetStopped() && on) {
		winchEncoder->Start();
	}
	
	else if (!winchEncoder->GetStopped() && !on) {
		winchEncoder->Stop();
	} 	
}

void Shootah::winchEncoderReset() {
	winchEncoder->Reset();
}

float Shootah::getWinchPID() {
	return winchPID->Get();
}

void Shootah::setCoffeeTable(bool state) {
	pneumaticCoffeeTable->Set(state); // TODO: Check if it is in a position that makes sense 
}

bool Shootah::getCoffeeTable() {
	return pneumaticCoffeeTable->Get();
}

void Shootah::setBloodyBogan(Shootah::ShifterPosition state) {
	if (pneumaticCoffeeTable->Get()) { // Saftey???
		pneumaticBloodyBogan->Set(state == Shootah::kActive ? true : false);
	}
}

Shootah::ShifterPosition Shootah::getBloodyBogan() {
	return pneumaticBloodyBogan->Get() ? Shootah::kActive : Shootah::kInactive;
}

bool Shootah::pullbackDone() {
	return pullbackSwitch->Get();
}

void Shootah::setWinchPIDState(bool state) {
	state ? winchPID->Enable() : winchPID->Disable();
}

/*Shootah::ShooterPosition Shootah::getShootahPosition() { // TODO: BAD
	if (pullbackSwitch->Get()) {
		return Shootah::kBack;
	}

	else if (!pullbackSwitch->Get() && pneumaticCoffeeTable->Get()) {
		return Shootah::kAdjusted;
	}

	else {
		return Shootah::kUnaligned;
	}
}*/
