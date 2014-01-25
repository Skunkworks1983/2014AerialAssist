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

#endif
