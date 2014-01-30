#include "Pterodactyl.h"
#include "../Robotmap.h"
#include "../Utils/SolenoidPair.h"

Pterodactyl::Pterodactyl() :
	Subsystem("Pterodactyl") {
	motorLeft = new PTERODACTYL_MOTOR_TYPE(PTERODACTYL_MOTOR_LEFT);
	motorRight = new PTERODACTYL_MOTOR_TYPE(PTERODACTYL_MOTOR_RIGHT);
	pot = new AnalogChannel(PTERODACTYL_POT);
	limNeg = new DigitalInput(PTERODACTYL_LIM_NEG);
	limPos = new DigitalInput(PTERODACTYL_LIM_POS);
	brake = new SolenoidPair(PTERODACTYL_BRAKE_ACTIVE, PTERODACTYL_BRAKE_DEACTIVE );
}

void Pterodactyl::InitDefaultCommand() {

}

double Pterodactyl::getAngle() {
	return (90*pot->GetAverageVoltage()*45) + 17.5;
}

void Pterodactyl::setAngleMotorSpeed(float speed) {
	if (((speed>0 && getAngle()<PTERODACTYL_MAX_ANGLE) || (speed<0
			&& getAngle()>PTERODACTYL_MIN_ANGLE)) && !getLimNeg() && !getLimPos()) {
		motorLeft->Set(speed);
		//motorRight->Set(-speed);
	}
	else {
		motorLeft->Set(0);
		//motorRight->Set(0);
	}
}

bool Pterodactyl::getLimNeg() {
	return limNeg->Get() != 0;
}

bool Pterodactyl::getLimPos() {
	return limPos->Get() != 0;
}

Pterodactyl::BrakeState Pterodactyl::getBrake() {
	return brake->Get() ? Pterodactyl::kActive : Pterodactyl::kDeactive;
}

void Pterodactyl::setBrakeState(Pterodactyl::BrakeState state) {
	brake->Set(state == Pterodactyl::kActive);
}