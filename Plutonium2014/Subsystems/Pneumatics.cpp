#include "Pneumatics.h"
#include "../Robotmap.h"
#include "WPILib.h"
#include "../Commands/UpdateCompressor.h"

Pneumatics::Pneumatics() :
	Subsystem("Pneumatics") {
	pressureSwitch = new DigitalInput(COMPRESSOR_PRESSURE_SENSOR);
	LiveWindow::GetInstance()->AddSensor("Pneumatics", "Pressure Switch", pressureSwitch);
	relay = new Relay(COMPRESSOR_RELAY);
	LiveWindow::GetInstance()->AddActuator("Pneumatics", "Compressor", relay);
}

void Pneumatics::InitDefaultCommand() {
	SetDefaultCommand(new UpdateCompressor());
}

void Pneumatics::setState(bool state) {
	relay->Set(state ? Relay::kForward : Relay::kOff);
}

bool Pneumatics::isCompressorOn() {
	return relay->Get() == Relay::kForward;
}

bool Pneumatics::isBelowPressure() {
	return !pressureSwitch->Get();
	
}

// Put methods for controlling this subsystem
// here. Call these from Commands.

