#ifndef SHOT_TUNING_H
#define SHOT_TUNING_H
#include "Robotmap.h"

#if COMPETITION_BOT
#define NEAR_SHOT_POWER 0.905
#define NEAR_SHOT_ANGLE 83.125

#define TRUSS_SHOT_POWER 1.0
#define TRUSS_SHOT_ANGLE 88.0

#else
#define NEAR_SHOT_POWER 0.95
#define NEAR_SHOT_ANGLE 88
#endif
#endif
