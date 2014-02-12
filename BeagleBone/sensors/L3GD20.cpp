/*
 * L3GD20.cpp
 *
 *  Created on: Feb 6, 2014
 *      Author: lwestin
 */

#include "L3GD20.h"
#include <stdio.h>
#include <math.h>

L3GD20::L3GD20() :
		I2C(L3GD20_ADDR) {
	res = DPS_2000;
	scalingValue = 0;
}

L3GD20::~L3GD20() {
}

void L3GD20::calibrate(Resolution res) {
	this->res = res;
	select();
	writeByte(L3GD20_CTREG1, L3GD20_ON);
	switch (res) {
	case DPS_250:
		writeByte(L3GD20_CTREG4, L3GD20_DPS250);
		scalingValue = (float) (250.0 / 32768.0);
		break;
	case DPS_500:
		writeByte(L3GD20_CTREG4, L3GD20_DPS500);
		scalingValue = (float) (500.0 / 32768.0);
		break;
	case DPS_2000:
	default:
		writeByte(L3GD20_CTREG4, L3GD20_DPS2000);
		scalingValue = (float) (2000.0 / 32768.0);
		break;
	}
}

float L3GD20::getRate(int lowAddr, int highAddr) {
	int data = (readByte(highAddr) << 8) + readByte(lowAddr);
	if (data >= 32768) {
		// Unsigned->signed brah
		int bits = floor((log(data) / log(2)) + 1);
		if (data >> (bits - 1)) {
			data -= 1 << (bits);
		}
	}
	return ((float) data) * scalingValue;
}
