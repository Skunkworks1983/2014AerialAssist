#ifndef ROBOTMAP_H
#define ROBOTMAP_H

#define COMPETITION_BOT 1

// ===============
// = Preferences =
// ===============
#define GET_FLOAT(x) (Preferences::GetInstance()->GetFloat(#x, x))
#define GET_DOUBLE(x) (Preferences::GetInstance()->GetDouble(#x, x))
#define GET_STRING(x) (Preferences::GetInstance()->GetString(#x, x))
#define GET_BOOL(x) (Preferences::GetInstance()->GetBoolean(#x, x))
#define GET_INT(x) (Preferences::GetInstance()->GetInt(#x, x))

#define SMARTDASH_VERBOSITY 15
#define ROBOT_VISUALIZATION false

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
// == Shooter ==
// =============
#define SHOOTER_MOTOR_WENCH TOP_SIDECAR,5
#define SHOOTER_CAT_POT 2
#define SHOOTER_PNEUMATIC_W_LATCH 8,7 /*R12 TBD*/
#define SHOOTER_PNEUMATIC_S_LATCH 5,6 /*L12 TBD*/
#define SHOOTER_S_LATCH_SENSOR TOP_SIDECAR,2 /*T2*/
#define SHOOTER_W_LATCH_SENSOR TOP_SIDECAR,1 /*T1*/
#define SHOOTER_SLATCH_PATTERN_DELAY (0) /* Milliseconds to delay slatch reaction */
#define SHOOTER_MOTOR_STALL_SPEED (0.05)
#define SHOOTER_MOTOR_STALL_TIME (1500)

#define SHOOTER_LIMITSWITCH 1
#if SHOOTER_LIMITSWITCH
#define SHOOTER_LIMITSWITCH_LEFT_PULLBACK_CHECK TOP_SIDECAR,6
#define SHOOTER_LIMITSWITCH_RIGHT_PULLBACK_CHECK TOP_SIDECAR,7
#define SHOOTER_LIMITSWITCH_DELAY (500) /* Milliseconds to delay proximity reaction */
#endif

#define SHOOTER_WENCH_ENCODER 8,9

#define SHOOTER_WENCH_POT_BACK (-0.0225)
#define SHOOTER_WENCH_POT_BACK_NEAR (0.08)

#define SHOOTER_WENCH_POT_REVERSE_ALLOW (0.1)

#define SHOOTER_PREPARE_SPEED 0.16
#define SHOOTER_WENCH_MOTOR_FULL_BACK (1.0)
#define SHOOTER_WENCH_MOTOR_FULL_BACK_NEAR (0.75)

#define SHOOTER_WENCH_MOTOR_FULL_RELEASE (-1.00)
#define SHOOTER_WENCH_MOTOR_FULL_RELEASE_NEAR (-0.35)
#define SHOOTER_WENCH_PAYOUT_TOLERANCE (0.01)
#define SHOOTER_WENCH_PAYOUT_TOLERANCE_NEAR (0.1)

#if COMPETITION_BOT
#define SHOOTER_POT_TO_DRAW_COEFF 0, 0.787401, -.08
#else
#define SHOOTER_POT_TO_DRAW_COEFF 0, 0.787401, -.09
#endif

#define SHOOTER_PATTERN_KILLZONE 200 /*Need a killzone in ms during which any changes are discarded*/

#define SHOOTER_SLATCH_WAIT 500
#define SHOOTER_WLATCH_WAIT 750

#define SHOOTER_WLATCH_LOCK_DRIVE 200 /*RUN MOTOR TIME TO LOCK IN MS*/
#define SHOOTER_WENCH_MOTOR_FORCE_LATCH (-1.0)
#define SHOOTER_WLATCH_UNLOCK_DRIVE 100 /*RUN MOTOR TIME TO UNLOCK IN MS*/
#define SHOOTER_WENCH_MOTOR_FORCE_UNLATCH (1.0)

#define SHOOTER_WENCH_POT_FULL_OUT (1.5)

// ===============
// == Collector ==
// ===============
#define COLLECTOR_BALL_SENSOR TOP_SIDECAR,3 /*T3*/
#define COLLECTOR_ROLLER_MOTOR_LEFT TOP_SIDECAR,6 /*T6*/
#define COLLECTOR_ROLLER_MOTOR_RIGHT TOP_SIDECAR,7 /*T7*/
#define COLLECTOR_CLAW_ENCODER_CHANNEL_A TOP_SIDECAR,4 /*T4*/
#define COLLECTOR_CLAW_ENCODER_CHANNEL_B TOP_SIDECAR,5 /*T5*/
#define COLLECTOR_JAW_SOLENOID_A (3) /*J1*/
#define COLLECTOR_JAW_SOLENOID_B (4) /*J2*/
#define COLLECTOR_ROLLER_TICKS_PER_ROTATION (256.0)
#define COLLECTOR_ROLLER_MAX_RPM (5000.0)
#define COLLECTOR_ROLLER_INTAKE_SET_POINT (5000)
#define COLLECTOR_ROLLER_STALL_SPEED (0.002)

// ===============
// == Automatic ==
// ===============
#define AUTO_DRIVE_DIST_STABILITY (2)	/*all values are arbitrary, need actual values*/
#define AUTO_DRIVE_DIST_THRESHOLD (.5)
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
#define AUTO_SHOT_ANGLE (80)
#define AUTO_SHOT_SCALAR (5)
#define AUTO_TURN_SLOW_DOWN (12)
#define AUTO_TURN_SPEED_MAX (.5)
#define AUTO_TURN_SPEED_MIN (.2)
#define AUTO_TURN_SPEED_RANGE (AUTO_TURN_SPEED_MAX - AUTO_TURN_SPEED_MIN)
#define AUTO_TURN_GYRO_THRESHOLD (.25)

// =================
// == Pterodactyl ==
// =================
// See Pterodactyl.cpp for PID defines

#define PTERODACTYL_POT (1)
#define PTERODACTYL_MOTOR_LEFT TOP_SIDECAR,9 /*T9*/
#define PTERODACTYL_MOTOR_RIGHT TOP_SIDECAR,8 /*T8*/
#define PTERODACTYL_BRAKE_ACTIVE TOP_SIDECAR,2
#define PTERODACTYL_MIN_ANGLE (0)
#define PTERODACTYL_MAX_ANGLE (90.0)
#define PTERODACTYL_ANGLE_THRESHOLD (2.0)

#define PTERODACTYL_POT_VOLTAGE_TO_ANGLE_COEFF (0), (56.845/PTERODACTYL_MAX_ANGLE), (-60/PTERODACTYL_MAX_ANGLE)

#define PTERODACTYL_POT_RATE_ZERO_THRESHOLD (-1)

// =================
// ====== OI =======
// =================
#define OI_JOYSTICK_LEFT (1)
#define OI_JOYSTICK_RIGHT (2)
#define PRACTICE_OI (0)
#define OI_JOYSTICK_DRIVE_DEADBAND (0.1)
#define OI_JOYSTICK_SQUIRRLY_POWER (2.0)
#define OI_ANALOG_TRESHOLD (0.1)
#define OI_SHOOTER_POWER_PORT (2)
#endif
