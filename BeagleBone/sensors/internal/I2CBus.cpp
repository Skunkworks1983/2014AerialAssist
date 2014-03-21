/*
 * I2CBus.cpp
 *
 *  Created on: Feb 6, 2014
 *      Author: lwestin
 */

#include "I2CBus.h"
#include <stdio.h>
#include <stdint.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <linux/i2c-dev.h>
#include <linux/i2c.h>
#include <sys/ioctl.h>
#include "smbus.h"

int I2CBus::fd = 0;
int I2CBus::references = 0;

I2CBus::I2CBus() {
}

I2CBus::~I2CBus() {
}

void I2CBus::allocateFD() {
	if (references <= 0) {
		char *fileName = "/dev/i2c-1";
		// Open port for reading and writing
		if ((fd = open(fileName, O_RDWR)) < 0) {
			perror("Failed to open /dev/i2c-1");
			exit(1);
		}
		references = 0;
	}
	references++;
}

void I2CBus::freeFD() {
	references--;
	if (references <= 0) {
		references = 0;
		close(fd);
	}
}

