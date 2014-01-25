#include "FireZeMissle.h"

FireZeMissle::FireZeMissle() {
	Requires(shootah);
}

void FireZeMissle::Initialize() {
	if (!shootah->getCoffeeTable()) {
		shootah->setCoffeeTable(true);
	}
	
	shootah->setBloodyBogan(Shootah::kInactive);
	shootah->setCoffeeTable(false);
}

void FireZeMissle::Execute() {
	
}

bool FireZeMissle::IsFinished() {
	return true;
}

void FireZeMissle::End() {
	
}

void FireZeMissle::Interrupted() {
}
