#include "FireZeMissle.h"

FireZeMissle::FireZeMissle() {
	Requires(shootah);
}

void FireZeMissle::Initialize() {
	/*if (!shootah->getLatch()) {
		shootah->setLatch(true);
	}
	shootah->setBrake(false);
	shootah->setLatch(false);*/
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
