#include "Pterodactyl.h"
#include "../Robotmap.h"
#include "../Utils/SolenoidPair.h"

Pterodactyl::Pterodactyl() :
	Subsystem("Pterodactyl") {
	motorLeft = new PTERODACTYL_MOTOR_TYPE(PTERODACTYL_MOTOR_LEFT);
	// TODO LiveWindow::GetInstance()->AddActuator("Pterodactyl", "Motor", motorLeft);
	motorRight = new PTERODACTYL_MOTOR_TYPE(PTERODACTYL_MOTOR_RIGHT);
	// TODO LiveWindow::GetInstance()->AddActuator("Pterodactyl", "Motor", motorRight);
	
	pot = new AnalogChannel(PTERODACTYL_POT);
	LiveWindow::GetInstance()->AddSensor("Pterodactyl", "Potentiometer", pot);
	
	brake = new SolenoidPair(PTERODACTYL_BRAKE_ACTIVE,
			PTERODACTYL_BRAKE_DEACTIVE);
	LiveWindow::GetInstance()->AddActuator("Pterodactyl", "Brake", brake);
}

void Pterodactyl::InitDefaultCommand() {

}

double Pterodactyl::getAngle() {
	return pot->GetAverageVoltage() * PTERODACTYL_VOLTAGE_TO_ANGLE;
	//^needs^to^be^tested^for^value^and^thing
}

void Pterodactyl::setAngleMotorSpeed(float speed) {
	if (((speed > 0 && getAngle() < PTERODACTYL_MAX_ANGLE) || (speed < 0
			&& getAngle() > PTERODACTYL_MIN_ANGLE))) {
		motorLeft->Set(speed);
		motorRight->Set(-speed);
	} else {
		motorLeft->Set(0);
		motorRight->Set(0);
	}
}

float Pterodactyl::getAngleMotorSpeed() {
	return motorLeft->Get();
}

Pterodactyl::BrakeState Pterodactyl::getBrake() {
	return (Pterodactyl::BrakeState) brake->Get();
}

void Pterodactyl::setBrakeState(Pterodactyl::BrakeState state) {
	brake->Set(state);
}

