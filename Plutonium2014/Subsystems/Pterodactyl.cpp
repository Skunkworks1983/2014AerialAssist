#include "Pterodactyl.h"
#include "../Robotmap.h"
#include "../Utils/Actuators/SolenoidPair.h"
#include "../Utils/Sensors/AnalogPot.h"
#include <math.h>
#include "../Utils/Actuators/DualLiveSpeed.h"

#define PTERODACTYL_P .75
#define PTERODACTYL_I .0105
#define PTERODACTYL_D 1.0
#define PTERODACTYL_ANGLE_THRESHOLD (3)

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

	setBrakeState(Pterodactyl::kActive);
	setAngleMotorSpeed(0);
	pid->Disable();
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
	if (target>40) {
		double p = 1615.3*pow(target, -1.578);
		double i = 2.375*pow(2.71, -.064*target);
		double d = 97.34*pow(target, -0.85);
		d /= 2.0;
		if (fabs(initialError) < 30) { // Extra corrections
			float divider = fabs(initialError);
			if (divider < 10) {
				divider = 10;
			}
			p *= 25.0 / divider;
			i *= 500.0 / (divider*divider);
		}
		pid->SetPID(p, i, d);
	} else {
		pid->SetPID(PTERODACTYL_P,PTERODACTYL_I, PTERODACTYL_D);
	}
	if (angle < 25) {
		pid->SetOutputRange(-.25, 0.75);
	} else {
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
	pid->Reset();
	this->target = target;
	this->initialError = target - getAngle();

	// PID values get updated here
	setOutputRange();

	pid->SetSetpoint((target+1) / (double) PTERODACTYL_MAX_ANGLE);

	// PID values get updated here (again because multithreading)
	setOutputRange();

	if (!pid->IsEnabled()) {
		pid->Enable();
	}
}

double Pterodactyl::getTarget() {
	return (pid->GetSetpoint() * (double) PTERODACTYL_MAX_ANGLE)-1.0;
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

bool Pterodactyl::isPIDFinished(bool ignorePIDState) {
	return (!ignorePIDState && !pid->IsEnabled()) || fabs(getTarget()
			-getAngle()) < PTERODACTYL_ANGLE_THRESHOLD;
}

