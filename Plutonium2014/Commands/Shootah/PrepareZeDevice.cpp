#include "PrepareZeDevice.h"
#include "../../Subsystems/Shootah.h"
#include "../../Robotmap.h"

#include "Latches/WLatch.h"
#include "ReleaseTension.h"

PrepareZeDevice::PrepareZeDevice(float setTurns) : CommandGroup("AutoCollect"){
	if (CommandBase::shootah->isReallyDrawnBack()) {
		AddSequential(new WLatch(true));
		AddSequential(new ReleaseTension(setTurns));
		AddSequential(new WLatch(false));
	}
}

void PrepareZeDevice::End() {
	
}

