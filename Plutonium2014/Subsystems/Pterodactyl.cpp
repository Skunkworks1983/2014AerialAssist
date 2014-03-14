#include "Pterodactyl.h"
#include "../Robotmap.h"
#include "../Utils/Actuators/SolenoidPair.h"
#include "../Utils/Sensors/AnalogPot.h"
#include <math.h>
#include "../Utils/Actuators/DualLiveSpeed.h"

#define PTERODACTYL_P 0.75
#define PTERODACTYL_I .011
#define PTERODACTYL_D .050
#define PTERODACTYL_ANGLE_THRESHOLD (1)

Pterodactyl::Pterodactyl() :
	Subsystem("Pterodactyl") {
	angleMotors = new DualLiveSpeed(new Talon(PTERODACTYL_MOTOR_LEFT),
			new Talon(PTERODACTYL_MOTOR_RIGHT), true);
	LiveWindow::GetInstance()->AddActuator("Pterodactyl", "Motor", angleMotors);

	pot = new AnalogPot(PTERODACTYL_POT);
	pot->SetAverageBits(2); // quadsample
	pot->setVoltageToAngle(PTERODACTYL_POT_VOLTAGE_TO_ANGLE_COEFF);

	LiveWindow::GetInstance()->AddSensor("Pterodactyl", "Potentiometer", pot);

	pid = new PIDController(PTERODACTYL_P, PTERODACTYL_I, PTERODACTYL_D,pot, this, 0.05f);
	pid->SetInputRange(-2.0, 2.0);
	pid->SetOutputRange(-1.0, 1.0);
	pid->SetAbsoluteTolerance(
	PTERODACTYL_ANGLE_THRESHOLD / (double) PTERODACTYL_MAX_ANGLE);
	LiveWindow::GetInstance()->AddActuator("Pterodactyl", "PID Controller", pid);
	SmartDashboard::PutData("Pterodactylz PID", pid);

	brake = new Relay(PTERODACTYL_BRAKE_ACTIVE);
	LiveWindow::GetInstance()->AddActuator("Pterodactyl", "Brake", brake);
}

void Pterodactyl::InitDefaultCommand() {

}

double Pterodactyl::getAngle() {
	return pot->GetAngle(0.0 / 100.0) * PTERODACTYL_MAX_ANGLE;
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
	float angle = getAngle();
	if (angle < 25) {
		pid->SetOutputRange(-.25, 0.75);
	} else {
		float speedUp = -0.25 * ((angle - 75.0) / 25.0) + 0.6;
		if (speedUp > 1.0) {
			speedUp = 1.0;
		} else if (speedUp < 0.4) {
			speedUp = 0.4;
		}
		pid->SetOutputRange(-.75, 0.75);
	}
}

float Pterodactyl::getPIDTarget() {
	return pid->GetSetpoint() * PTERODACTYL_MAX_ANGLE;
}

void Pterodactyl::PIDWrite(float f) {
	angleMotors->Set(f);
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
	if (pid->IsEnabled()) {
		pid->Disable();
	}
	pid->SetSetpoint(target / (double) PTERODACTYL_MAX_ANGLE);
	pid->Reset();
	float iScale = 1.0;
	if (target <= 75) {
		iScale = 1.1;
	} else if (target>=90) {
		iScale = 0.9;
	}
	pid->SetPID(PTERODACTYL_P, PTERODACTYL_I * iScale, PTERODACTYL_D);
	if (!pid->IsEnabled()) {
		pid->Enable();
	}
}

void Pterodactyl::stopPID() {
	if (pid->IsEnabled()) {
		pid->Disable();
		angleMotors->Set(0);
	}
}

void Pterodactyl::writeAngleMotorRaw(float f) {
	angleMotors->Set(f);
}

double Pterodactyl::PIDGet() {
	return getAngle();
}

bool Pterodactyl::isPIDFinished() {
	return !pid->IsEnabled() || fabs( (pid->GetSetpoint()
			* PTERODACTYL_MAX_ANGLE) - getAngle()) < GET_DOUBLE(PTERODACTYL_ANGLE_THRESHOLD);
}

