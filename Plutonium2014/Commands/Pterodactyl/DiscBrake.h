#ifndef __DISC_BRAKE_H
#define __DISC_BRAKE_H

#include "../../CommandBase.h"

enum Pterodactyl::BrakeState;
/**
 *
 *
 * @author David ;)
 */
class DiscBrake: public CommandBase {
private:
	Pterodactyl::BrakeState state;
public:
	DiscBrake(Pterodactyl::BrakeState state);
	virtual void Initialize();
	virtual void Execute();
	virtual bool IsFinished();
	virtual void End();
	virtual void Interrupted();
};

#endif
