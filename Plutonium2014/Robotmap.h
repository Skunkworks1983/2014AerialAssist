#ifndef ROBOTMAP_H
#define ROBOTMAP_H

// ================
// == Pneumatics ==
// ================
#define COMPRESSOR_RELAY (1)
#define COMPRESSOR_PRESSURE_SENSOR (5)

// ===============
// == DriveBase ==
// ===============
#define DRIVE_MOTOR_TYPE Talon
#define DRIVE_MOTOR_FRONT_LEFT 1
#define DRIVE_MOTOR_FRONT_RIGHT 2
#define DRIVE_MOTOR_BACK_LEFT 3
#define DRIVE_MOTOR_BACK_RIGHT 4
#define DRIVE_ENCODER_RIGHT 8,9
#define DRIVE_ENCODER_LEFT 6,7
#define DRIVE_SHIFT_HIGH 1
#define DRIVE_SHIFT_LOW 2

// =============
// == Shootah ==
// =============
// Actual values not here yet, 
#define SHOOTAH_MOTOR_WINCH 8
#define SHOOTAH_ENCODER_WINCH 1,2
#define SHOOTAH_PNEUMATIC_COFFEE_TABLE 3,4
#define SHOOTAH_PNEUMATIC_BLOODY_BOGAN 12,13
#define SHOOTAH_LIMITSWITCH_PULLBACK_CHECK 14

#define SHOOTAH_DRAW_POSITION_FULL 12345
//#define SHOOTAH_DRAW_POSITION_HALF 54321

// ===============
// == Collector ==
// ===============
#define COLLECTOR_BALL_SENSOR (1)
#define COLLECTOR_JAW_STATE (2)
#define COLLECTOR_ROLLER_MOTOR (5)
#define COLLECTOR_CLAW_ENCODER_CHANNEL_A (10)
#define COLLECTOR_CLAW_ENCODER_CHANNEL_B (11)
#define COLLECTOR_JAW_SOLENOID_A (1)
#define COLLECTOR_JAW_SOLENOID_B (2)
#define COLLECTOR_ROLLER_300_ROTATIONS_PER_TICK (1.0/300.0/254.0)

// ===============
// == Automatic ==
// ===============
#define AUTO_DRIVE_DIST_STABILITY (1)	//all values are arbitrary, need actual values
#define AUTO_DRIVE_DIST_THRESHOLD (1)
#define AUTO_DRIVE_DIST_SPEED_MIN (.1)
#define AUTO_DRIVE_DIST_SPEED_MAX (.75)
#define AUTO_DRIVE_DIST_SLOW_DOWN (.5)

// =================
// == Pterodactyl ==
// =================
#define PTERODACTYL_POT 1
#define PTERODACTYL_MAX_ANGLE 90
#define PTERODACTYL_MIN_ANGLE 0
#define THRESHOLD_LOWER 10
#define THRESHOLD_UPPER 10
#define LIL_BIT 2
#define PTERODACTYL_MOTOR_LEFT 6
//#define PTERODACTYL_MOTOR_RIGHT 5
#define PTERODACTYL_LIM_NEG 13
#define PTERODACTYL_LIM_POS 14
#define PTERODACTYL_UP .25
#define PTERODACTYL_DOWN -.25
#define PTERODACTYL_UP_NEAR .125
#define PTERODACTYL_DOWN_NEAR -.125
#define PTERODACTYL_MOTOR_TYPE Talon

#endif
