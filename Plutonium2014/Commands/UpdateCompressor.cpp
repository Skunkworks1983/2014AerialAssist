#include "UpdateCompressor.h"

UpdateCompressor::UpdateCompressor() {

}

void UpdateCompressor::Initialize() {
	
}

void UpdateCompressor::Execute() {
	pneumatics->setState(pneumatics->isBelowPressure());
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
