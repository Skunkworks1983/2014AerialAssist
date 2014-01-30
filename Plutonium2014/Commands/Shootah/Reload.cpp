#include "Reload.h"
#include "DrawZeDevice.h"
#include "PrepareZeDevice.h"

Reload::Reload(float setpoint) {
	CommandGroup("Shoot");
	AddSequential(new DrawZeDevice());
	AddSequential(new PrepareZeDevice(setpoint));
}

Reload::~Reload() {
}