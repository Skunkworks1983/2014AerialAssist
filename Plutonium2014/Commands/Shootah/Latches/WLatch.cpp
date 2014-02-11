#include "WLatch.h"
#include "../../../Utils/Time.h"
#include "../../../Robotmap.h"

WLatch::WLatch(bool state) {
	Requires(shootah);
	this->state = state;
	time = 0;
	bTime = getCurrentMillis();
}

void WLatch::Initialize() {
	shootah->setWLatch(state);
}

void WLatch::Execute() {
	time = getCurrentMillis() - bTime;
}

bool WLatch::IsFinished() {
	printf("Latch: %d\n", shootah->getWLatch());
	if(shootah->getWLatch() == state) {
		return true;
	}
		
	else if (time >= SHOOTAH_WLATCH_WAIT){
		printf("error stuff\n");
		// error stuff aka dankSuperdawg
		return true;
	}

	return false;
}

void WLatch::End() {
	
}

void WLatch::Interrupted() {
}
