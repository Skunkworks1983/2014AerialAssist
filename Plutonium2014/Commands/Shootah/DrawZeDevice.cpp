#include "DrawZeDevice.h"

DrawZeDevice::DrawZeDevice() {
	Requires(shootah);
}

void DrawZeDevice::Initialize() {
	
}

void DrawZeDevice::Execute() {
	
}

bool DrawZeDevice::IsFinished() { // Just starting this, umm, yeah
	if (shootah->getShootahPosition() != Shootah::kBack) {
		return false;
	}
}

void DrawZeDevice::End() {
	
}

void DrawZeDevice::Interrupted() {
}
