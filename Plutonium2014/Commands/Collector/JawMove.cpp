#include "JawMove.h"

JawMove::JawMove(Collector::JawState state, float timeout) :
			CommandBase(
					CommandBase::createNameFromString("JawMove",
							state == Collector::kClosed ? "Closed" : "Open")) {
	Requires(collector);
	SetTimeout(timeout);
	this->state = state;
}

void JawMove::Initialize() {
	killIt = false;
	if (collector->getJawState() == state) {
		killIt = true;
	}
}

void JawMove::Execute() {
	if (shooter->isReallyDrawnBack()) {
		collector->setJawState(state);
	}
}

bool JawMove::IsFinished() {
	return killIt || IsTimedOut();
}

void JawMove::End() {

}

void JawMove::Interrupted() {

}
