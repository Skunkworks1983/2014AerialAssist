/*
 * LSM303.h
 *
 *  Created on: Feb 6, 2014
 *      Author: lwestin
 */

#ifndef LSM303_ACC_H_
#define LSM303_ACC_H_

#include "internal/I2C.h"

#define LSM303_LSM_ACC_ADDR 0x19

#define LSM303_CTRL_REG1_A 0x20
#define LSM303_CTRL_REG4_A 0x23
#define LSM303_OUT_X_L_A 0x28
#define LSM303_OUT_X_H_A 0x29
#define LSM303_OUT_Y_L_A 0x2A
#define LSM303_OUT_Y_H_A 0x2B
#define LSM303_OUT_Z_L_A 0x2C
#define LSM303_OUT_Z_H_A 0x2D
#define LSM303_POWER_ON 0b10010111		// ON LSM303 ACC. and 1.344 KHz mode
class LSM303_ACC: public I2C {
public:
	enum Scale {
		SCALE_A_2G = -2, SCALE_A_4G = -4, SCALE_A_8G = -8, SCALE_A_16G = -16
	};
private:
	Scale scale;
	float getRate(int lowAddr, int highAddr);
public:
	LSM303_ACC();
	virtual ~LSM303_ACC();
	void setup(Scale s = SCALE_A_8G);

	inline float getX() {
		return getRate(LSM303_OUT_X_L_A, LSM303_OUT_X_H_A);
	}
	inline float getY() {
		return getRate(LSM303_OUT_Y_L_A, LSM303_OUT_Y_H_A);
	}
	inline float getZ() {
		return getRate(LSM303_OUT_Z_L_A, LSM303_OUT_Z_H_A);
	}
};

#endif /* LSM303_H_ */
