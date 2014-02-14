#include "UpdateCompressor.h"

UpdateCompressor::UpdateCompressor() {
	Requires(pneumatics);
}

void UpdateCompressor::Initialize() {
	ticksSinceUpdate = 0;
}

void UpdateCompressor::Execute() {
	if(ticksSinceUpdate > 10){
		pneumatics->setState(pneumatics->isBelowPressure());
		ticksSinceUpdate = 0;
	}
	++ticksSinceUpdate;
}

/**
 * Always returns false because command is intended to be run constantly
 */
bool UpdateCompressor::IsFinished() {
	return false;
}

/**
 * Turns off compressor to prevent burning it out
 */
void UpdateCompressor::End() {
	pneumatics->setState(false);
}

/**
 * If command is interrupted, run End command to shut compressor off
 */
void UpdateCompressor::Interrupted() {
	End();
}
