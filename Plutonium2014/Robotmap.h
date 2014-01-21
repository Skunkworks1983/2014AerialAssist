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
#define SHOOTAH_MOTOR_WINCH 1
#define SHOOTAH_ENCODER_WINCH 1,2
#define SHOOTAH_PNEUMATIC_COFFEE_TABLE 1
#define SHOOTAH_PNEUMATIC_WANKER 2
#define SHOOTAH_LIMITSWITCH_PULLBACK_CHECK 1

#endif
