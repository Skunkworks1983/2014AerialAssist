#include "JawMove.h"

JawMove::JawMove(Collector::JawState state) :
	CommandBase(CommandBase::createNameFromString("JawMove", state
			==Collector::kClosed ? "Closed" : "Open")) {
	Requires(collector);
	SetTimeout(0.125);
	this->state = state;
}

void JawMove::Initialize() {

}

void JawMove::Execute() {
	collector->setJawState(state);
}

bool JawMove::IsFinished() {
	return IsTimedOut();//state==collector->getJawState();
}

void JawMove::End() {

}

void JawMove::Interrupted() {

}
