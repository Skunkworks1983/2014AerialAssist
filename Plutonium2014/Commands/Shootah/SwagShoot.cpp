#include "SwagShoot.h"
#include "DrawZeDevice.h"
#include "PrepareZeDevice.h"
#include "FireZeMissle.h"

SwagShoot::SwagShoot(float setpoint) {
	CommandGroup("NoScope");
	AddSequential(new DrawZeDevice());
	AddSequential(new PrepareZeDevice(setpoint));
	AddSequential(new FireZeMissle());
}

SwagShoot::~SwagShoot() {
}
