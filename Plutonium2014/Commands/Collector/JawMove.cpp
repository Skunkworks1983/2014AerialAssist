#include "JawMove.h"

JawMove::JawMove(bool closed) :
			CommandBase(
					CommandBase::createNameFromString("JawMove",
							closed ? "Closed" : "Open")) {
	Requires(collector);
	this->state = closed;
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
