#include <stdio.h>
#include <stdint.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <linux/i2c-dev.h>
#include <linux/i2c.h>
#include <sys/ioctl.h>
#include "smbus.h"
#include <math.h>
#include "BMP180.h"
#include "L3GD20.h"

int mainz(int argc, char **argv) {
	BMP180 *bmp = new BMP180();
	bmp->calibrate();

	L3GD20 *gyro = new L3GD20();
	gyro->calibrate();

	unsigned int temperature = bmp->getTemperature();
	unsigned int pressure = bmp->getPressure();
	unsigned int altitude = bmp->getAltitude(pressure);

	printf("Temperature\t%0.1f *F\n", ((double) temperature) / 10 * 1.8 + 32);
	printf("Pressure\t%0.2f hPa\n", ((double) pressure) / 100);
	printf("Altitude\t%0.1f Feet\n", ((double) altitude) * 3.280839895);
	for (int i = 0; i < 1000; i++) {
		printf("RATE: %5.5f\t%5.5f\t%5.5f\n", gyro->getXRate(), gyro->getYRate(),
				gyro->getZRate());
		usleep(100000);
	}

	delete bmp;
	delete gyro;

	return 0;
}
