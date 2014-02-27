#include "Autonomous.h" 
#include "../Automatic/AutoDriveDistance.h"

#define AUTO_SCRIPT_CHARMASK(a,b) ((((int)a) << 8) | ((int)b))

Autonomous::Autonomous() :
	CommandGroup("Autonomous-Blank") {
}

Autonomous::Autonomous(char *style) :
	CommandGroup(style) {
}

Autonomous::~Autonomous() {

}

void Autonomous::Initialize() {
}
