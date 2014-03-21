#include "LSM303_ACC.h"
#include <math.h>

LSM303_ACC::LSM303_ACC() :
		I2C(LSM303_LSM_ACC_ADDR) {
	scale = SCALE_A_8G;
}

LSM303_ACC::~LSM303_ACC() {

}

void LSM303_ACC::setup(Scale s) {
	select();
	scale = s;
	writeByte(LSM303_CTRL_REG1_A, LSM303_POWER_ON);
	switch (scale) {
	case SCALE_A_2G:
		writeByte(LSM303_CTRL_REG4_A,0b00001000);
		break;
	case SCALE_A_4G:
		writeByte(LSM303_CTRL_REG4_A,0b00011000);
		break;
	case SCALE_A_8G:
		writeByte(LSM303_CTRL_REG4_A,0b00101000);
		break;
	case SCALE_A_16G:
		writeByte(LSM303_CTRL_REG4_A,0b00111000);
		break;
	}
}

float LSM303_ACC::getRate(int lowAddr, int highAddr) {
	int data = (readByte(highAddr) << 8) + readByte(lowAddr);
	if (data >= 32768) {
		// Unsigned->signed brah
		int bits = floor((log(data) / log(2)) + 1);
		if (data >> (bits - 1)) {
			data -= 1 << (bits);
		}
	}
	return ((float) data) * ((float) scale) / 32768.0;
}
