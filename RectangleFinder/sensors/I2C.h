/*
 * I2C.h
 *
 *  Created on: Feb 6, 2014
 *      Author: lwestin
 */

#ifndef I2C_H_
#define I2C_H_

#include <linux/i2c-dev.h>

class I2C {
private:
	int address;
public:
	I2C(int address);
	virtual ~I2C();
	void select();

	__s32 readInt(__u8 address);
	void writeByte(__u8 address, __u8 value);
	void readBlock(__u8 address, __u8 length, __u8 *values);
	__s32 readByte(__u8 address);
};

#endif /* I2C_H_ */
