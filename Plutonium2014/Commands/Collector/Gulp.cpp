#include "Gulp.h"

// Backend
#include "../../Robotmap.h"

Gulp::Gulp() :
	CommandBase("Gulp") {
}

Gulp::~Gulp() {
}

void Gulp::Initialize() {
	SetTimeout(0.25);
	collector->setJawState(Collector::kOpen);
	collector->setRollerSpeed(COLLECTOR_ROLLER_INTAKE_SET_POINT);
}

void Gulp::Execute() {
}

bool Gulp::IsFinished() {
	return IsTimedOut();
}

void Gulp::End() {
	collector->setJawState(Collector::kClosed);
	collector->setRollerSpeed(0);
}

void Gulp::Interrupted() {
	collector->setJawState(Collector::kClosed);
	collector->setRollerSpeed(0);
}
