#include "DrawZeDevice.h"
#include "../../Subsystems/Shootah.h"
#include "../../Robotmap.h"

#include "Latches/SLatch.h"
#include "Latches/WLatch.h"
#include "DrawShootahBack.h"

DrawZeDevice::DrawZeDevice() :
	CommandGroup("DrawZeDevice") {
	AddSequential(new SLatch(Shootah::kLatched));
	AddSequential(new WLatch(Shootah::kUnlatched));
	AddSequential(new DrawShootahBack());
	AddSequential(new WLatch(Shootah::kLatched));
}

void DrawZeDevice::Initialize() {
	SetInterruptible(false);
}

void DrawZeDevice::End() {
	//CommandBase::shootah->setPrepared(false);
}

