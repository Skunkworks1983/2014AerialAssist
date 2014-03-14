#include "ResetShooter.h"

ResetShooter::ResetShooter() :
	CommandBase("ResetShooter") {
}

void ResetShooter::Initialize() {
	shooter->resetShooter();
}

void ResetShooter::Execute() {
}

bool ResetShooter::IsFinished() {
	return true;
}

void ResetShooter::End() {
}

void ResetShooter::Interrupted() {
}
