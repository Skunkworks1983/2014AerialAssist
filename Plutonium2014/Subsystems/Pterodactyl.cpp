#include "Pterodactyl.h"
#include "../Robotmap.h"
#include "../Utils/SolenoidPair.h"
#include "../Utils/AnalogPot.h"
#include <math.h>
#include "../Utils/DualLiveSpeed.h"

Pterodactyl::Pterodactyl() :
	Subsystem("Pterodactyl") {
	angleMotors = new DualLiveSpeed(
			new Talon(PTERODACTYL_MOTOR_LEFT),
			new Talon(PTERODACTYL_MOTOR_RIGHT), true);
	LiveWindow::GetInstance()->AddActuator("Pterodactyl", "Motor", angleMotors);

	pot = new AnalogPot(PTERODACTYL_POT);
	pot->setVoltageToAngle(PTERODACTYL_POT_VOLTAGE_TO_ANGLE_COEFF);

	LiveWindow::GetInstance()->AddSensor("Pterodactyl", "Potentiometer", pot);

	pid = new PIDController(PTERODACTYL_PID_DOWN, pot, angleMotors, 0.05f);
	pid->SetInputRange(-2.0, 2.0);
	pid->SetOutputRange(-.5, .6);
	pid->SetAbsoluteTolerance(
	PTERODACTYL_ANGLE_THRESHOLD / (double) PTERODACTYL_MAX_ANGLE);
	LiveWindow::GetInstance()->AddActuator("Pterodactyl", "PID Controller", pid);
	SmartDashboard::PutData("Pterodactyl PID", pid);

	brake = new Relay(PTERODACTYL_BRAKE_ACTIVE);
	LiveWindow::GetInstance()->AddActuator("Pterodactyl", "Brake", brake);
}

void Pterodactyl::InitDefaultCommand() {

}

double Pterodactyl::getAngle() {
	return pot->GetAngle() * PTERODACTYL_MAX_ANGLE;
}
double Pterodactyl::getRate() {
	return pot->GetRate() * PTERODACTYL_MAX_ANGLE;
}

void Pterodactyl::setAngleMotorSpeed(float speed) {
	if (((speed > 0 && getAngle() < PTERODACTYL_MAX_ANGLE) || (speed < 0
			&& getAngle() >PTERODACTYL_MIN_ANGLE))) {
		angleMotors->Set(speed);
	} else {
		angleMotors->Set(0);
	}
}

void Pterodactyl::setOutputRange() {
	float scaler = fabs((pid->GetSetpoint() * PTERODACTYL_MAX_ANGLE)
			- getAngle())>10 ? 1 : .85;
	if (pid->GetSetpoint() > getAngle()) {
		pid->SetPID(PTERODACTYL_PID_UP);
	} else {
		pid->SetPID(PTERODACTYL_PID_DOWN);
	}
	if (getAngle() > 90) {
		pid->SetOutputRange(-0.4*scaler, 0.25*scaler);
	} else if (getAngle() > 60) {
		pid->SetOutputRange(-0.1*scaler, 0.5*scaler);
	} else {
		pid->SetOutputRange(0, 0.6*scaler);
	}
}

float Pterodactyl::getAngleMotorSpeed() {
	return angleMotors->Get();
}

Pterodactyl::BrakeState Pterodactyl::getBrake() {
	return (Pterodactyl::BrakeState) brake->Get();
}

void Pterodactyl::setBrakeState(Pterodactyl::BrakeState state) {
	brake->Set(state == Pterodactyl::kActive ? Relay::kOff : Relay::kForward);
}

void Pterodactyl::setTarget(float target) {
	pid->SetSetpoint(target / (double) PTERODACTYL_MAX_ANGLE);
	pid->Reset();
	if (!pid->IsEnabled()) {
		pid->Enable();
	}

}

void Pterodactyl::stopPID() {
	if (pid->IsEnabled()) {
		pid->Disable();
	}
}

bool Pterodactyl::isPIDFinished() {
	return fabs((pid->GetSetpoint() * PTERODACTYL_MAX_ANGLE) - getAngle())
			< PTERODACTYL_ANGLE_THRESHOLD;
}

