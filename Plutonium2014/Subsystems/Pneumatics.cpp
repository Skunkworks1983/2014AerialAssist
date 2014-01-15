#include "Pneumatics.h"
#include "../Robotmap.h"
#include "WPILib.h"
#include "../Commands/UpdateCompressor.h"

Pneumatics::Pneumatics() :
	Subsystem("Pneumatics") {
	pressureSwitch = new DigitalInput(1);
	relay = new Relay(1, Relay::kBothDirections);
}

void Pneumatics::InitDefaultCommand() {
	SetDefaultCommand(new UpdateCompressor());
}

void Pneumatics::setState(bool state) {
	relay->Set(state ? Relay::kOn : Relay::kOff);
}

bool Pneumatics::isBelowPressure() {
	return !pressureSwitch->Get();
}

// Put methods for controlling this subsystem
// here. Call these from Commands.

