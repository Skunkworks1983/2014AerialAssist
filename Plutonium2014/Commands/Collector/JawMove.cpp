#include "JawMove.h"

JawMove::JawMove(bool state) {
	Requires(collector);
	this->state = state;
}

void JawMove::Initialize() {
	
}

void JawMove::Execute() {
	collector->setJawState(state);
}

bool JawMove::IsFinished() {
	return collector->getJawState();
}

void JawMove::End() {
	
}

void JawMove::Interrupted() {
	
}
