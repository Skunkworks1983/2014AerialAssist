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
	pot->SetAverageBits(2); // quadsample
	pot->setVoltageToAngle(PTERODACTYL_POT_VOLTAGE_TO_ANGLE_COEFF);

	LiveWindow::GetInstance()->AddSensor("Pterodactyl", "Potentiometer", pot);

	pid = new PIDController(PTERODACTYL_PID_UP,pot,  this, 0.05f);
	pid->SetInputRange(-2.0, 2.0);
	pid->SetOutputRange(-1.0, 1.0);
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
	return pot->GetAngle(2.0 / 100.0) * PTERODACTYL_MAX_ANGLE;
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

#define SCALING 0.75

void Pterodactyl::setOutputRange() {
	if (getAngle() < 25) {
		pid->SetOutputRange(-.125 * SCALING, 1.0);
	} else {
		pid->SetOutputRange(-.4, getAngle() > 75 ? 0.5 : 1.0);
	}
}

float Pterodactyl::getPIDTarget() {
	return pid->GetSetpoint() * PTERODACTYL_MAX_ANGLE;
}

void Pterodactyl::PIDWrite(float f) {
	float neutralSpeed = 0.3 - (8.0e-7 * pow(getAngle() + 10, 2.63));
	neutralSpeed *= SCALING;
	float output = f + neutralSpeed;
	if (output < -1.0) {
		output = -1.0;
	} else if (output > 1.0) {
		output = 1.0;
	}

	float scaling;
	if (output < 1.0) {
		// Going down
		scaling = sin(getAngle() / 125.0 * 3.141592 / 2.0) * 0.25 + 0.75;
	} else {
		// Going up
		scaling = cos(getAngle() / 125.0 * 3.141592 / 2.0) * 0.25 + 0.75;
	}

	if (goingUp) {
		float dScale = (pid->GetSetpoint() * 0.5) + 0.5;
		pid->SetPID(PTERODACTYL_PID_UP* dScale);
	} else {
		float dScale = (pid->GetSetpoint() * 0.75) + 0.25;
		pid->SetPID(PTERODACTYL_PID_DOWN*dScale);
	}

	//	printf("Motor: %f\tCorrection: %f\tOutput: %f\tScale: %f\n", f,
				//			neutralSpeed, output, scaling);
				//	printf("PID Values: %f,%f,%f\n", pid->GetP(), pid->GetI(), pid->GetD());
				angleMotors->Set(output * scaling);
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
	if (target > getAngle()) {
		goingUp = true;
		float dScale = (pid->GetSetpoint() * 0.5) + 0.5;
		printf("DScaling UP At: %f\n", dScale);
		pid->SetPID(PTERODACTYL_PID_UP* dScale);
	} else {
		goingUp = false;
		float dScale = (pid->GetSetpoint() * 0.75) + 0.25;
		printf("DScaling DOWN At: %f\n", dScale);
		pid->SetPID(PTERODACTYL_PID_DOWN*dScale);
	}
	pid->Reset();
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

bool Pterodactyl::isPIDFinished() {
	return fabs((pid->GetSetpoint() * PTERODACTYL_MAX_ANGLE) - getAngle())
			< GET_DOUBLE(PTERODACTYL_ANGLE_THRESHOLD);
}

