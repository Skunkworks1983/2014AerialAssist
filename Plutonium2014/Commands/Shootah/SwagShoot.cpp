#include "SwagShoot.h"
//#include "DrawZeDevice.h"
//#include "PrepareZeDevice.h"
#include "FireZeMissle.h"
#include "../../Commands/DriveBase/TurnDegree.h"

SwagShoot::SwagShoot() {
	CommandGroup("NoScope");
	AddSequential(new TurnDegree(360));
	//AddSequential(new DrawZeDevice());
	//AddSequential(new PrepareZeDevice(SHOOTAH_PREPARE_SET_POINT));
	AddSequential(new FireZeMissle());
}

SwagShoot::~SwagShoot() {
}
