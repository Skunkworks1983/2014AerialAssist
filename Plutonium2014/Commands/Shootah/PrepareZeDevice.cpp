#include "PrepareZeDevice.h"
#include "../../Subsystems/Shootah.h"
#include "../../Robotmap.h"

#include "Latches/WLatch.h"
#include "ReleaseTension.h"

PrepareZeDevice::PrepareZeDevice(float setTurns) :
	CommandGroup("PrepareZeDevice") {
	AddSequential(new WLatch(Shootah::kUnlatched));
	AddSequential(new ReleaseTension(setTurns));
	AddSequential(new WLatch(Shootah::kLatched));
}

void PrepareZeDevice::Initialize() {
	SetInterruptible(false);
}

void PrepareZeDevice::End() {
	//CommandBase::shootah->setPrepared(true);
}

