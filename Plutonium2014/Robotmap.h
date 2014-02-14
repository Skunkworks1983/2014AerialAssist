#ifndef ROBOTMAP_H
#define ROBOTMAP_H

// ================
// ==  Sidecars  ==
// ================
#define TOP_SIDECAR 2
#define BOTTOM_SIDECAR 1

// ================
// == Pneumatics ==
// ================
#define COMPRESSOR_RELAY (BOTTOM_SIDECAR,1) /*S1*/
#define COMPRESSOR_PRESSURE_SENSOR (BOTTOM_SIDECAR,1) /*BD1*/

// ===============
// == DriveBase ==
// ===============
#define DRIVE_MOTOR_TYPE Talon
#define DRIVE_MOTOR_FRONT_LEFT BOTTOM_SIDECAR,4
#define DRIVE_MOTOR_FRONT_RIGHT BOTTOM_SIDECAR,2
#define DRIVE_MOTOR_BACK_LEFT BOTTOM_SIDECAR,3
#define DRIVE_MOTOR_BACK_RIGHT BOTTOM_SIDECAR,1
#define DRIVE_ENCODER_RIGHT BOTTOM_SIDECAR,2,BOTTOM_SIDECAR,3 /*TODO*/
#define DRIVE_ENCODER_LEFT BOTTOM_SIDECAR,7,BOTTOM_SIDECAR,8 /*TODO*/
#define DRIVE_SHIFT_HIGH 1
#define DRIVE_SHIFT_LOW 2
#define MOTOR_MAX 0.95
#define TOO_DAMN_SLOW 1000 //Half what the encoder should be at full speed (was 6000 on blocks at full speed)

// =============
// == Shootah ==
// =============
// Actual values not here yet, 
#define SHOOTAH_MOTOR_WENCH TOP_SIDECAR,5
#define SHOOTAH_CAT_POT 2
#define SHOOTAH_PNEUMATIC_W_LATCH 8,7 /*R12 TBD*/
#define SHOOTAH_PNEUMATIC_S_LATCH 5,6 /*L12 TBD*/
#define SHOOTAH_W_LATCH_SENSOR 2 /* DOES NOT EXIST */
#define SHOOTAH_S_LATCH_SENSOR TOP_SIDECAR,2 /*T2*/

#define SHOOTAH_PNEUMATIC_BRAKE 12345,23456 /*DNE*/
#define SHOOTAH_LIMITSWITCH_LEFT_PULLBACK_CHECK BOTTOM_SIDECAR,4 /*SOON*/
#define SHOOTAH_LIMITSWITCH_RIGHT_PULLBACK_CHECK 13 /*SOON*/

#define SHOOTAH_WENCH_ENCODER 8,9
#define SHOOTAH_WENCH_POT_BACK 0

#define SHOOTAH_PREPARE_SPEED 0.16
#define SHOOTAH_WENCH_MOTOR_FULL_BACK (0.37)
#define SHOOTAH_WENCH_MOTOR_FULL_FORWARD (-0.25)
#define SHOOTAH_PREPARE_SET_POINT 2
#define SHOOTAH_SLOOP -2
#define SHOOTAH_YCEPT 9.992
#define SHOOTAH_WENCH_POT_TO_DRAW(x) ((x-2.365) / .75) /* 2.5 = voltage at full draw, .75 = voltage at release - voltage at full */

#define SHOOTAH_SLATCH_WAIT 500
#define SHOOTAH_WLATCH_WAIT 500

// ===============
// == Collector ==
// ===============
#define COLLECTOR_BALL_SENSOR TOP_SIDECAR,3 /*T3*/
#define COLLECTOR_JAW_STATE TOP_SIDECAR,1 /*T1*/
#define COLLECTOR_ROLLER_MOTOR_LEFT TOP_SIDECAR,6 /*T6*/
#define COLLECTOR_ROLLER_MOTOR_RIGHT TOP_SIDECAR,7 /*T7*/
#define COLLECTOR_CLAW_ENCODER_CHANNEL_A TOP_SIDECAR,4 /*T4*/
#define COLLECTOR_CLAW_ENCODER_CHANNEL_B TOP_SIDECAR,5 /*T5*/
#define COLLECTOR_JAW_SOLENOID_A (3) /*J1*/
#define COLLECTOR_JAW_SOLENOID_B (4) /*J2*/
#define COLLECTOR_ROLLER_TICKS_PER_ROTATION (256.0)
#define COLLECTOR_ROLLER_MAX_RPM (1200.0)
#define COLLECTOR_ROLLER_INTAKE_SET_POINT CRISP

// ===============
// == Automatic ==
// ===============
#define AUTO_DRIVE_DIST_STABILITY (1)	//all values are arbitrary, need actual values
#define AUTO_DRIVE_DIST_THRESHOLD (1)
#define AUTO_DRIVE_DIST_SPEED_MIN (.1)
#define AUTO_DRIVE_DIST_SPEED_MAX (.75)
#define AUTO_DRIVE_DIST_SLOW_DOWN (.5)
#define AUTO_TURN_SPEED_MAX (.5)
#define AUTO_TURN_SPEED_MIN (.2)
#define AUTO_TURN_SPEED_RANGE (AUTO_TURN_SPEED_MAX - AUTO_TURN_SPEED_MIN)
#define AUTO_TURN_SLOW_DOWN (12)
#define AUTO_TURN_GYRO_THRESHOLD (.25)

// =================
// == Pterodactyl ==
#define CRISP (.16)
#define a2 2
// =================
#define PTERODACTYL_POT (1)
#define PTERODACTYL_MAX_ANGLE 90
#define PTERODACTYL_MIN_ANGLE 0
#define THRESHOLD_LOWER 10
#define THRESHOLD_UPPER 10
#define LIL_BIT 2
#define PTERODACTYL_MOTOR_LEFT TOP_SIDECAR,9 /*T9*/
#define PTERODACTYL_MOTOR_RIGHT TOP_SIDECAR,8 /*T8*/
#define PTERODACTYL_LIM_NEG 12
#define PTERODACTYL_LIM_POS 13
#define PTERODACTYL_UP .25
#define PTERODACTYL_DOWN -.25
#define PTERODACTYL_UP_NEAR .125
#define PTERODACTYL_DOWN_NEAR -.125
#define PTERODACTYL_MOTOR_TYPE Talon
#define PTERODACTYL_BRAKE_ACTIVE TOP_SIDECAR,2 // THIS IS A RELAY. TODO: duh it doesn't work
#define PTERODACTYL_BRAKE_DEACTIVE 11+a2 /*DNE JUST SET ACTIVE TO FALSE AND SPRINGS BACK*/
#define PTERODACTYL_POT_ADJUST_SLOPE 34992.22
#define PTERODACTYL_POT_ADJUST_ZERO 4.964695
#define PTERODACTYL_VOLTAGE_TO_ANGLE 720

#endif
