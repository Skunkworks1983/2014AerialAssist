/*
 * BMP180.cpp
 *
 *  Created on: Feb 6, 2014
 *      Author: lwestin
 */

#include "BMP180.h"
#include <unistd.h>
#include <math.h>

BMP180::BMP180() :
		I2C(0x77) {
	ac1 = 0;
	ac2 = 0;
	ac3 = 0;
	ac4 = 0;
	ac5 = 0;
	ac6 = 0;
	b1 = 0;
	b2 = 0;
	mb = 0;
	mc = 0;
	md = 0;
	b5 = 0;
}

BMP180::~BMP180() {
}

void BMP180::calibrate() {
	select();
	ac1 = readInt(0xAA);
	ac2 = readInt(0xAC);
	ac3 = readInt(0xAE);
	ac4 = readInt(0xB0);
	ac5 = readInt(0xB2);
	ac6 = readInt(0xB4);
	b1 = readInt(0xB6);
	b2 = readInt(0xB8);
	mb = readInt(0xBA);
	mc = readInt(0xBC);
	md = readInt(0xBE);
}

unsigned int BMP180::readUT() {
	unsigned int ut = 0;

	// Write 0x2E into Register 0xF4
	// This requests a temperature reading
	writeByte(0xF4, 0x2E);

	// Wait at least 4.5ms
	usleep(5000);

	// Read the two byte result from address 0xF6
	ut = readInt(0xF6);

	return ut;
}

unsigned int BMP180::readUP() {
	unsigned int up = 0;
	// Write 0x34+(BMP085_OVERSAMPLING_SETTING<<6) into register 0xF4
	// Request a pressure reading w/ oversampling setting
	writeByte(0xF4, 0x34 + (BMP085_OVERSAMPLING_SETTING << 6));

	// Wait for conversion, delay time dependent on oversampling setting
	usleep((2 + (3 << BMP085_OVERSAMPLING_SETTING)) * 1000);

	// Read the three byte result from 0xF6
	// 0xF6 = MSB, 0xF7 = LSB and 0xF8 = XLSB
	__u8 values[3];
	readBlock(0xF6, 3, values);

	up = (((unsigned int) values[0] << 16) | ((unsigned int) values[1] << 8)
			| (unsigned int) values[2]) >> (8 - BMP085_OVERSAMPLING_SETTING);

	return up;
}

unsigned int BMP180::getPressure() {
	unsigned int up = readUP();

	int x1, x2, x3, b3, b6, p;
	unsigned int b4, b7;

	b6 = b5 - 4000;
	// Calculate B3
	x1 = (b2 * (b6 * b6) >> 12) >> 11;
	x2 = (ac2 * b6) >> 11;
	x3 = x1 + x2;
	b3 = (((((int) ac1) * 4 + x3) << BMP085_OVERSAMPLING_SETTING) + 2) >> 2;

	// Calculate B4
	x1 = (ac3 * b6) >> 13;
	x2 = (b1 * ((b6 * b6) >> 12)) >> 16;
	x3 = ((x1 + x2) + 2) >> 2;
	b4 = (ac4 * (unsigned int) (x3 + 32768)) >> 15;

	b7 = ((unsigned int) (up - b3) * (50000 >> BMP085_OVERSAMPLING_SETTING));
	if (b7 < 0x80000000)
		p = (b7 << 1) / b4;
	else
		p = (b7 / b4) << 1;

	x1 = (p >> 8) * (p >> 8);
	x1 = (x1 * 3038) >> 16;
	x2 = (-7357 * p) >> 16;
	p += (x1 + x2 + 3791) >> 4;

	return p;
}

unsigned int BMP180::getTemperature() {
	unsigned int ut = readUT();
	int x1, x2;

	x1 = (((int) ut - (int) ac6) * (int) ac5) >> 15;
	x2 = ((int) mc << 11) / (x1 + md);
	b5 = x1 + x2;

	unsigned int result = ((b5 + 8) >> 4);

	return result;
}

unsigned int BMP180::getAltitude(float pressure) {
	float A = pressure / 101794.58;
	float B = 1 / 5.25588;
	float C = pow(A, B);
	C = 1 - C;
	C = C / 0.0000225577;
	return C;
}
