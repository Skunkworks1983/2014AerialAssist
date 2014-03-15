#include "JawMove.h"

JawMove::JawMove(Collector::JawState state, float timeout) :
			CommandBase(
					CommandBase::createNameFromString("JawMove",
							state == Collector::kClosed ? "Closed" : "Open")) {
	Requires(collector);
	SetTimeout(timeout);
	this->state = state;
	this->killIt = false;
}

void JawMove::Initialize() {
	killIt = false;
	if (collector->getJawState() == state) {
		//killIt = true; NO SKETCHY
	}
	collector->setJawState(state);
}

void JawMove::Execute() {
	//if (shooter->isReallyDrawnBack()) { NO SKETCHY
		collector->setJawState(state);
	//}
}

bool JawMove::IsFinished() {
	return killIt || IsTimedOut();
}

void JawMove::End() {

}

void JawMove::Interrupted() {

}
