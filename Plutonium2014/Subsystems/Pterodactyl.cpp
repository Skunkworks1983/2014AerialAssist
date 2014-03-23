#include "Pterodactyl.h"
#include "../Robotmap.h"
#include "../Utils/Actuators/SolenoidPair.h"
#include "../Utils/Sensors/AnalogPot.h"
#include <math.h>
#include "../Utils/Actuators/DualLiveSpeed.h"
#include "../Utils/Controllers/PID1983Controller.h"

#define PTERODACTYL_P 2.5
#define PTERODACTYL_I .5
#define PTERODACTYL_D 0.5
#define PTERODACTYL_ANGLE_THRESHOLD (2.0)

#define PID_EQUATION_METHOD 1

Pterodactyl::Pterodactyl() :
	Subsystem("Pterodactyl") {
	angleMotors = new DualLiveSpeed(new Talon(PTERODACTYL_MOTOR_LEFT),
			new Talon(PTERODACTYL_MOTOR_RIGHT), true);
	LiveWindow::GetInstance()->AddActuator("Pterodactyl", "Motor", angleMotors);

	pot = new AnalogPot(PTERODACTYL_POT);
	pot->SetAverageBits(2); // quadsample
	pot->setVoltageToAngle(PTERODACTYL_POT_VOLTAGE_TO_ANGLE_COEFF);

	LiveWindow::GetInstance()->AddSensor("Pterodactyl", "Potentiometer", pot);
#if PID_EQUATION_METHOD
	pid = new PID1983Controller(PTERODACTYL_P, PTERODACTYL_I, PTERODACTYL_D,pot, this, 0.05f);
#else
	pid
	= new PID1983Controller(PTERODACTYL_P, PTERODACTYL_I, PTERODACTYL_D,pot, this, 0.05f / 4.0f);
#endif
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

	SmartDashboard::PutNumber("ptero_maxITerm", .150);
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
#if PID_EQUATION_METHOD
	double p, i, d;
	if (target>40) {
		//		float volts = DriverStation::GetInstance()->GetBatteryVoltage(); TODO Can I make it adaptive?
		p = 1615.3*pow(target, -1.578);
		i = 2.0*pow(2.71, -.055*target);
		d = 97.34*pow(target, -0.85);
		d /= 2.0;
		if (fabs(initialError) < 30) { // Extra corrections
			float divider = fabs(initialError);
			if (divider <7.5) {
				divider = 7.5;
			}
			if (initialError < 0) {
				p *= 25.0 / divider;
				i *= 125.0 / divider;
			} else {
				p *= 25.0 / divider;
				i *= 250.0 / divider;
			}
		}
	} else {
		p = .75;
		i = .0105;
		d = .05;
	}
	pid->SetPID(p, i, d);
#else
	pid->m_maximumITerm = SmartDashboard::GetNumber("ptero_maxITerm");
#endif
	if (initialError> 0) {
		if (angle < 25) {
			pid->SetOutputRange(-.25, 0.75);
		} else {
			pid->SetOutputRange(-.75, 0.75);
		}
	} else {
		pid->SetOutputRange(-.35, 1.0);
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

	pid->SetSetpoint(target / (double) PTERODACTYL_MAX_ANGLE);

	// PID values get updated here (again because multithreading)
	setOutputRange();

	if (!pid->IsEnabled()) {
		pid->Enable();
	}
}

double Pterodactyl::getTarget() {
	return (pid->GetSetpoint() * (double) PTERODACTYL_MAX_ANGLE);
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

