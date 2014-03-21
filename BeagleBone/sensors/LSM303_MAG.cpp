#include "LSM303_MAG.h"
#include <math.h>

LSM303_MAG::LSM303_MAG() :
		I2C(LSM303_ADDRESS_MAG) {
	gain = GAIN_1_9;
}

LSM303_MAG::~LSM303_MAG() {

}

void LSM303_MAG::setup(MagGain s) {
	select();
	gain = s;
	writeByte(LSM303_REGISTER_MAG_MR_REG_M, 0x00);
	writeByte(LSM303_REGISTER_MAG_CRB_REG_M, (unsigned char) gain);
}

float LSM303_MAG::getAxis(int lowAddr, int highAddr) {
	int data = (readByte(highAddr) << 8) + readByte(lowAddr);
	if (data >= 32768) {
		// Unsigned->signed brah
		int bits = floor((log(data) / log(2)) + 1);
		if (data >> (bits - 1)) {
			data -= 1 << (bits);
		}
	}
	return ((float) data) / 600.0f;
}
