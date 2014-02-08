#include "SLatch.h"
#include "../../../Utils/Time.h"
#include "../../../Robotmap.h"

SLatch::SLatch(bool state) {
	Requires(shootah);
	this->state = state;
	time = 0;
	bTime = getCurrentMillis();
}

void SLatch::Initialize() {
	shootah->setSLatch(state);
}

void SLatch::Execute() {
	time = getCurrentMillis() - bTime;
}

bool SLatch::IsFinished() {
	if(shootah->getSLatch() == state) {
		return true;
	}
		
	else if (time >= SHOOTAH_SLATCH_WAIT){
		// Shutting down the shooter
		return true;
	}
	
	return false;
}

void SLatch::End() {
	
}

void SLatch::Interrupted() {
}
