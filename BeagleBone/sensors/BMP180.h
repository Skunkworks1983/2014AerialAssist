/*
 * BMP180.h
 *
 *  Created on: Feb 6, 2014
 *      Author: lwestin
 */

#ifndef BMP180_H_
#define BMP180_H_

#include "internal/I2C.h"

class BMP180: public I2C {
private:
	static const unsigned char BMP085_OVERSAMPLING_SETTING = 3;

	// Calibration values - These are stored in the BMP085
	short int ac1;
	short int ac2;
	short int ac3;
	unsigned short int ac4;
	unsigned short int ac5;
	unsigned short int ac6;
	short int b1;
	short int b2;
	short int mb;
	short int mc;
	short int md;
	int b5;

	unsigned int readUT();
	unsigned int readUP();
public:
	BMP180();
	virtual ~BMP180();

	void calibrate();
	unsigned int getPressure();
	unsigned int getTemperature();
	unsigned int getAltitude(float pressure);
};

#endif /* BMP180_H_ */
