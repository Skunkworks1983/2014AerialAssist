#include "DiscBrake.h"
// CSTDLIB
#include <math.h>

// Backend
#include "../../Robotmap.h"

DiscBrake::DiscBrake(Pterodactyl::BrakeState state) :
	CommandBase(CommandBase::createNameFromString("DiscBrake", state
			== Pterodactyl::kActive ? "Active" : "Deactive")) {
	Requires(pterodactyl);
	this->state = state;
}

void DiscBrake::Initialize() {
	pterodactyl->setBrakeState(state);
}

void DiscBrake::Execute() {
}

bool DiscBrake::IsFinished() {
	return true;
}

void DiscBrake::End() {
}

void DiscBrake::Interrupted() {
}
