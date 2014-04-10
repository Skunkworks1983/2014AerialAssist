#ifndef SHOT_TUNING_H
#define SHOT_TUNING_H
#include "Robotmap.h"

#if COMPETITION_BOT
#define AUTO_1_SHOT_POWER 0.914
#define AUTO_1_SHOT_ANGLE 90.5

#define NEAR_SHOT_POWER 0.947
#define NEAR_SHOT_ANGLE 84.0

#define TRUSS_SHOT_POWER 0.9
#define TRUSS_SHOT_ANGLE 90.0

#else
#define NEAR_SHOT_POWER 0.95
#define NEAR_SHOT_ANGLE 88
#endif
#endif
