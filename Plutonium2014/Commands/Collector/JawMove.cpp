#include "JawMove.h"

JawMove::JawMove(bool isUp) {
	Requires(collector);
	this->isUp = isUp;
}

void JawMove::Initialize() {
	
}

void JawMove::Execute() {
	collector->setJawState(isUp);
}

bool JawMove::IsFinished() {
	return collector->getJawState();
}

void JawMove::End() {
	
}

void JawMove::Interrupted() {
	
}
