/*
 * LSM303.h
 *
 *  Created on: Feb 6, 2014
 *      Author: lwestin
 */

#ifndef LSM303_MAG_H_
#define LSM303_MAG_H_

#include "internal/I2C.h"

#define LSM303_ADDRESS_MAG	(0x3C >> 1)
#define LSM303_REGISTER_MAG_CRA_REG_M 0x00
#define LSM303_REGISTER_MAG_CRB_REG_M 0x01
#define LSM303_REGISTER_MAG_MR_REG_M 0x02
#define LSM303_REGISTER_MAG_OUT_X_H_M 0x03
#define LSM303_REGISTER_MAG_OUT_X_L_M 0x04
#define LSM303_REGISTER_MAG_OUT_Z_H_M 0x05
#define LSM303_REGISTER_MAG_OUT_Z_L_M 0x06
#define LSM303_REGISTER_MAG_OUT_Y_H_M 0x07
#define LSM303_REGISTER_MAG_OUT_Y_L_M 0x08
#define LSM303_REGISTER_MAG_SR_REG_Mg 0x09
#define LSM303_REGISTER_MAG_IRA_REG_M 0x0A
#define LSM303_REGISTER_MAG_IRB_REG_M 0x0B
#define LSM303_REGISTER_MAG_IRC_REG_M 0x0C
#define LSM303_REGISTER_MAG_TEMP_OUT_H_M 0x31
#define LSM303_REGISTER_MAG_TEMP_OUT_L_M 0x32

#define LSM303_POWER_ON 0b10010111		// ON LSM303 ACC. and 1.344 KHz mode
class LSM303_MAG: public I2C {
public:
	enum MagGain {
		GAIN_1_3 = 0x20,  // +/- 1.3
		GAIN_1_9 = 0x40,  // +/- 1.9
		GAIN_2_5 = 0x60,  // +/- 2.5
		GAIN_4_0 = 0x80,  // +/- 4.0
		GAIN_4_7 = 0xA0,  // +/- 4.7
		GAIN_5_6 = 0xC0,  // +/- 5.6
		GAIN_8_1 = 0xE0   // +/- 8.1
	};
private:
	MagGain gain;
	float getAxis(int lowAddr, int highAddr);
public:
	LSM303_MAG();
	virtual ~LSM303_MAG();
	void setup(MagGain gain = GAIN_1_9);

	inline float getX() {
		return getAxis(LSM303_REGISTER_MAG_OUT_X_L_M, LSM303_REGISTER_MAG_OUT_X_H_M);
	}
	inline float getY() {
		return getAxis(LSM303_REGISTER_MAG_OUT_Y_L_M, LSM303_REGISTER_MAG_OUT_Y_H_M);
	}
	inline float getZ() {
		return getAxis(LSM303_REGISTER_MAG_OUT_Z_L_M, LSM303_REGISTER_MAG_OUT_Z_H_M);
	}
};

#endif /* LSM303_H_ */
