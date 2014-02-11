#include "SLatch.h"
#include "../../../Utils/Time.h"
#include "../../../Robotmap.h"

SLatch::SLatch(bool isLocked) {
	Requires(shootah);
	this->isLocked = isLocked;
	time = 0;
	bTime = getCurrentMillis();
}

void SLatch::Initialize() {
	if (!isLocked && !shootah->isReallyDrawnBack()) {
		shootah->setSLatch(isLocked);
	}
	
	else if (!isLocked && shootah->isReallyDrawnBack()) {
		shootah->setSLatch(!isLocked);
	}
	
	else {
		shootah->setSLatch(isLocked);
	}
}

void SLatch::Execute() {
	time = getCurrentMillis() - bTime;
}

bool SLatch::IsFinished() {
	if(shootah->getSLatch() == isLocked) {
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
