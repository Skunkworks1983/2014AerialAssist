#include "Pterodactyl.h"
#include "../Robotmap.h"
#include "../Utils/Actuators/SolenoidPair.h"
#include "../Utils/Sensors/AnalogPot.h"
#include <math.h>
#include "../Utils/Actuators/DualLiveSpeed.h"

Pterodactyl::Pterodactyl() :
	Subsystem("Pterodactyl") {
	angleMotors = new DualLiveSpeed(new Talon(PTERODACTYL_MOTOR_LEFT),
			new Talon(PTERODACTYL_MOTOR_RIGHT), true);
	LiveWindow::GetInstance()->AddActuator("Pterodactyl", "Motor", angleMotors);

	pot = new AnalogPot(PTERODACTYL_POT);
	pot->setVoltageToAngle(PTERODACTYL_POT_VOLTAGE_TO_ANGLE_COEFF);

	LiveWindow::GetInstance()->AddSensor("Pterodactyl", "Potentiometer", pot);

	pid = new PIDController(PTERODACTYL_PID_DOWN_0, pot, angleMotors, 0.05f);
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
			&& getAngle() > PTERODACTYL_MIN_ANGLE))) {
		angleMotors->Set(speed);
	} else {
		angleMotors->Set(0);
	}
}

void Pterodactyl::setOutputRange() {
	float dScale = 1.0;
	float error = (pid->GetSetpoint() * PTERODACTYL_MAX_ANGLE) - getAngle();
	if (fabs(error) > 25) {
		dScale = 0.125;
	} else if (fabs(error) > 15) {
		dScale = 0.75;
	} else {
		dScale = 1.0;
	}

	float pScale = 1.0;
	if (fabs(error) > 45) {
		pScale = 2.0;
	} else {
		pScale = 1.0;
	}
	
	const float scaler = 1.0;
	if (pid->GetSetpoint() < getAngle()) {
		pid->SetPID(pScale * PTERODACTYL_PID_DOWN_0* dScale);
	} else if (getAngle() < 60) {
		pid->SetPID(pScale * PTERODACTYL_PID_UP_60 * dScale);
	} else {
		pid->SetPID(pScale * PTERODACTYL_PID_UP_90 * dScale);
	}
	if (getAngle() > 90) {
		pid->SetOutputRange(-0.4 * scaler, 0.5 * scaler);
	} else if (getAngle() > 60) {
		pid->SetOutputRange(-0.1 * scaler, 0.8 * scaler);
	} else {
		pid->SetOutputRange(0, scaler);
	}
}

void Pterodactyl::resetPID() {
	pid->Reset();
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

