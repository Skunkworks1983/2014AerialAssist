#include "AutoStupidDrive.h"

AutoStupidDrive::AutoStupidDrive(double timeout, float speed) {
	Requires(driveBase);
	SetTimeout(timeout);
	this->speed = speed;
}
void AutoStupidDrive::Initialize() {
	printf("Stupid drive\n");
	driveBase->setDriveGear(DriveBase::kHigh);
}
void AutoStupidDrive::Execute() {
	driveBase->setSpeed(speed, speed);
}
bool AutoStupidDrive::IsFinished() {
	return IsTimedOut();
}
void AutoStupidDrive::End() {
	driveBase->setSpeed(0, 0);
}
void AutoStupidDrive::Interrupted() {
	driveBase->setSpeed(0, 0);
}