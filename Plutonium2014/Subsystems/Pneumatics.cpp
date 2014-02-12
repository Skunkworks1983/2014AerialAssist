#include "Pneumatics.h"
#include "../Robotmap.h"
#include "WPILib.h"
#include "../Commands/UpdateCompressor.h"

Pneumatics::Pneumatics() :
	Subsystem("Pneumatics") {
	pressureSwitch = new DigitalInput(COMPRESSOR_PRESSURE_SENSOR);
	relay = new Relay(COMPRESSOR_RELAY, Relay::kForwardOnly);
}

void Pneumatics::InitDefaultCommand() {
	SetDefaultCommand(new UpdateCompressor());
}

void Pneumatics::setState(bool state) {
	relay->Set(state ? Relay::kForward : Relay::kOff);
}

bool Pneumatics::isBelowPressure() {
	return !pressureSwitch->Get();
}

// Put methods for controlling this subsystem
// here. Call these from Commands.

