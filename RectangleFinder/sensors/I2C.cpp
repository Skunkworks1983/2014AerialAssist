/*
 * I2C.cpp
 *
 *  Created on: Feb 6, 2014
 *      Author: lwestin
 */

#include "I2C.h"
#include <stdio.h>
#include <stdint.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <linux/i2c-dev.h>
#include <linux/i2c.h>
#include <sys/ioctl.h>
#include "smbus.h"
#include "I2CBus.h"

I2C::I2C(int address) {
	this->address = address;
	I2CBus::allocateFD();
}

I2C::~I2C() {
	I2CBus::freeFD();
}

void I2C::select() {
	// Set the port options and set the address of the device
	if (ioctl(I2CBus::getFD(), I2C_SLAVE, address) < 0) {
		perror("Failed to select");
	}
}

__s32 I2C::readInt(__u8 address) {
	__s32 res = i2c_smbus_read_word_data(I2CBus::getFD(), address);
	if (res < 0) {
		printf("READ INT FAILED\n");
	}
	res = ((res << 8) & 0xFF00) | ((res >> 8) & 0xFF);
	return res;
}

void I2C::writeByte(__u8 address, __u8 value) {
	if (i2c_smbus_write_byte_data(I2CBus::getFD(), address, value) < 0) {
		printf("WRITE BYTE FAILED\n");
	}
}

void I2C::readBlock(__u8 address, __u8 length, __u8 *values) {
	if (i2c_smbus_read_i2c_block_data(I2CBus::getFD(), address, length, values) < 0) {
		printf("READ BLOCK FAILED\n");
	}
}


__s32 I2C::readByte(__u8 address) {
	__s32 res = i2c_smbus_read_byte_data(I2CBus::getFD(), address);
	if (res < 0) {
		printf("READ BYTE FAILED\n");
	}
	return res;
}
