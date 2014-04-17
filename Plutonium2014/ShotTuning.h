#ifndef SHOT_TUNING_H
#define SHOT_TUNING_H
#include "Robotmap.h"

#if COMPETITION_BOT
#define NEAR_SHOT_POWER 0.94
#define NEAR_SHOT_ANGLE 84.0

#define AUTO_1_SHOT_POWER NEAR_SHOT_POWER
#define AUTO_1_SHOT_ANGLE NEAR_SHOT_ANGLE

#define TRUSS_SHOT_POWER 0.95
#define TRUSS_SHOT_ANGLE 89.0

#define SHOOTER_POWER_TURNS_1 (0.5)

#define STEEP_SHOT_POWER (0.9)
#define STEEP_SHOT_ANGLE (90.5)

#else
#define NEAR_SHOT_POWER 0.94
#define NEAR_SHOT_ANGLE 84.0

#define AUTO_1_SHOT_POWER NEAR_SHOT_POWER
#define AUTO_1_SHOT_ANGLE NEAR_SHOT_ANGLE

#define TRUSS_SHOT_POWER 0.95
#define TRUSS_SHOT_ANGLE 89.0

#define SHOOTER_POWER_TURNS_1 (0.5)

#define STEEP_SHOT_POWER (0.9)
#define STEEP_SHOT_ANGLE (90.5)
#endif
#endif
