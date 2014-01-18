#ifndef __SHOOTAH_H
#define __SHOOTAH_H
#include "Commands/Subsystem.h"
#include "WPILib.h"
#include "../Utils/SolenoidPair.h"

/**
 *
 *
 * @author David
 */
class Shootah: public Subsystem {
public:
	enum ShooterPosition{
		kShoot,
		kReload
	};
private:
	SolenoidPair *shooterPneumatics;
	ShooterPosition *cachedPosition;
public:
	Shootah();
	void InitDefaultCommand();
	void shooterSet(ShooterPosition position);
	ShooterPosition getPosition();
	
};

#endif
