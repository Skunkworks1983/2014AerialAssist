#include "Shootah.h"
#include "../Robotmap.h"

Shootah::Shootah() :
	Subsystem("Shootah") {
	shooterPneumatics = new SolenoidPair(4,5);
	*cachedPosition = Shootah::kShoot;
}

void Shootah::InitDefaultCommand() {
	
}

void Shootah::shooterSet(Shootah::ShooterPosition position) {
	shooterPneumatics->Set(position == Shootah::kShoot ? true : false);
}

Shootah::ShooterPosition Shootah::getPosition() {
	return shooterPneumatics->Get() ? Shootah::kShoot : Shootah::kReload;
}
// Put methods for controlling this subsystem
// here. Call these from Commands.

