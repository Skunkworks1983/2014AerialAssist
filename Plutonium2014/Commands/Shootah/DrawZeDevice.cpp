#include "DrawZeDevice.h"
#include "../../Subsystems/Shootah.h"
#include "../../Robotmap.h"

#include "Latches/SLatch.h"
#include "Latches/WLatch.h"
#include "DrawShootahBack.h"

DrawZeDevice::DrawZeDevice() :
	CommandGroup("DrawZeDevice") {
	AddSequential(new SLatch(true));
	AddSequential(new WLatch(true));
	AddSequential(new DrawShootahBack());
	AddSequential(new WLatch(false));
}

void DrawZeDevice::Initialize() {
	SetInterruptible(false);
}

void DrawZeDevice::End() {
	//CommandBase::shootah->setPrepared(false);
}

