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
#define COMPRESSOR_RELAY BOTTOM_SIDECAR,1 /*S1*/
#define COMPRESSOR_PRESSURE_SENSOR BOTTOM_SIDECAR,2 /*BD1*/

// ===============
// == DriveBase ==
// ===============
#define DRIVE_MOTOR_TYPE Talon
#define DRIVE_MOTOR_FRONT_LEFT BOTTOM_SIDECAR,4
#define DRIVE_MOTOR_FRONT_RIGHT BOTTOM_SIDECAR,2
#define DRIVE_MOTOR_BACK_LEFT BOTTOM_SIDECAR,3
#define DRIVE_MOTOR_BACK_RIGHT BOTTOM_SIDECAR,1
#define DRIVE_ENCODER_RIGHT BOTTOM_SIDECAR,3,BOTTOM_SIDECAR,4 /*TODO*/
#define DRIVE_ENCODER_LEFT BOTTOM_SIDECAR,5,BOTTOM_SIDECAR,6 /*TODO*/
#define DRIVE_SHIFT_HIGH 1
#define DRIVE_SHIFT_LOW 2

// =============
// == Shootah ==
// =============
#define SHOOTAH_MOTOR_WENCH TOP_SIDECAR,5
#define SHOOTAH_CAT_POT 2
#define SHOOTAH_PNEUMATIC_W_LATCH 8,7 /*R12 TBD*/
#define SHOOTAH_PNEUMATIC_S_LATCH 5,6 /*L12 TBD*/
#define SHOOTAH_S_LATCH_SENSOR TOP_SIDECAR,2 /*T2*/

#if SHOOTAH_LIMITSWITCH
#define SHOOTAH_LIMITSWITCH_LEFT_PULLBACK_CHECK BOTTOM_SIDECAR,9 /*TODO SOON*/
#define SHOOTAH_LIMITSWITCH_RIGHT_PULLBACK_CHECK 13 /*SOON TODO*/
#endif

#define SHOOTAH_WENCH_ENCODER 8,9
#define SHOOTAH_WENCH_POT_BACK 0

#define SHOOTAH_PREPARE_SPEED 0.16
#define SHOOTAH_WENCH_MOTOR_FULL_BACK (1.0)
#define SHOOTAH_WENCH_MOTOR_FULL_BACK_NEAR (0.75)
#define SHOOTAH_WENCH_SETPOINT_THRESH (0.08)

#define SHOOTAH_WENCH_MOTOR_FULL_RELEASE (-0.25)
#define SHOOTAH_WENCH_PAYOUT_TOLERANCE (0.1)

#define SHOOTAH_POT_TO_DRAW_COEFF 0, 1.0, -2.25 /*0, 1.0, -2.365*/

#define SHOOTAH_PATTERN_KILLZONE 200 /*Need a killzone in ms after which any changes are discarded*/

#define SHOOTAH_SLATCH_WAIT 500
#define SHOOTAH_WLATCH_WAIT 500

#define SHOOTAH_WLATCH_LOCK_DRIVE 200 /*RUN MOTOR TIME TO LOCK IN MS*/
#define SHOOTAH_WENCH_MOTOR_FORCE_LATCH (-1.0)
#define SHOOTAH_WLATCH_UNLOCK_DRIVE 200 /*RUN MOTOR TIME TO UNLOCK IN MS*/
#define SHOOTAH_WENCH_MOTOR_FORCE_UNLATCH (1.0)

#define SHOOTAH_WENCH_POT_FULL_OUT (1.25)

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
#define COLLECTOR_ROLLER_INTAKE_SET_POINT (1000)

// ===============
// == Automatic ==
// ===============
#define AUTO_DRIVE_DIST_STABILITY (1)	/*all values are arbitrary, need actual values*/
#define AUTO_DRIVE_DIST_THRESHOLD (1)
#define AUTO_DRIVE_DIST_SPEED_MIN (.1)
#define AUTO_DRIVE_DIST_SPEED_MAX (.75)
#define AUTO_DRIVE_DIST_SLOW_DOWN (.5)
#define AUTO_DRIVE_DIST_SLOW_DOWN (.5)
#define AUTO_DRIVE_DIST_CATCHUP	(5)
#define AUTO_TURN_SPEED_MAX (.5)
#define AUTO_TURN_SPEED_MIN (.2)
#define AUTO_TURN_SPEED_RANGE (AUTO_TURN_SPEED_MAX - AUTO_TURN_SPEED_MIN)
#define AUTO_TURN_SLOW_DOWN (12)
#define AUTO_TURN_GYRO_THRESHOLD (.25)

// =================
// == Pterodactyl ==
// =================
#define PTERODACTYL_PID_UP 1.5, .15, 7.0
#define PTERODACTYL_PID_DOWN 1.5, .15, 4.0
#define PTERODACTYL_POT (1)
#define PTERODACTYL_ANGLE_THRESHOLD (5)
#define PTERODACTYL_MOTOR_LEFT TOP_SIDECAR,9 /*T9*/
#define PTERODACTYL_MOTOR_RIGHT TOP_SIDECAR,8 /*T8*/
#define PTERODACTYL_BRAKE_ACTIVE TOP_SIDECAR,2
#define PTERODACTYL_MIN_ANGLE (0)
#define PTERODACTYL_MAX_ANGLE (90.0)
#define PTERODACTYL_POT_VOLTAGE_TO_ANGLE_COEFF (0), (56.845/PTERODACTYL_MAX_ANGLE), (-62.489/PTERODACTYL_MAX_ANGLE)
#define PTERODACTYL_POT_RATE_ZERO_THRESHOLD (-1)

// =================
// ====== OI =======
// =================
#define OI_JOYSTICK_LEFT (1)
#define OI_JOYSTICK_RIGHT (2)
#define OI_JOYSTICK_DRIVE_DEADBAND (0.05)
#define OI_JOYSTICK_SQUIRRLY_POWER (2.0)
#define OI_ANALOG_TRESHOLD (0.2)
#define OI_SHOOTER_POWER_PORT (2)
#define SHOOTER_POWER_TURNS_1 (0.5)
#define SHOOTER_POWER_TURNS_2 (0.75)
#define SHOOTER_POWER_TURNS_3 (1.1)
#endif
