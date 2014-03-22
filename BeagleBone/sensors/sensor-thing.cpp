#include <stdio.h>
#include <stdint.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <linux/i2c-dev.h>
#include <linux/i2c.h>
#include <sys/ioctl.h>
#include "internal/smbus.h"
#include <math.h>
#include "BMP180.h"
#include "L3GD20.h"
#include "LSM303_ACC.h"
#include "LSM303_MAG.h"
#include "kalman/Kalman.h"
#include <time.h>

int main(int argc, char **argv) {
	BMP180 *bmp = new BMP180();
	bmp->calibrate();

	L3GD20 *gyro = new L3GD20();
	gyro->calibrate();

	LSM303_ACC *acc = new LSM303_ACC();
	acc->setup();

	LSM303_MAG *mag = new LSM303_MAG();
	mag->setup();

	FreeIMU *imu = new FreeIMU();
	imu->gyro = gyro;
	imu->baro = bmp;
	imu->acc = acc;
	imu->mag = mag;

	sleep(1);
	imu->init();

	unsigned int temperature = bmp->getTemperature();
	unsigned int pressure = bmp->getPressure();
	unsigned int altitude = bmp->getAltitude(pressure);

	printf("Temperature\t%0.1f *F\n", ((double) temperature) / 10 * 1.8 + 32);
	printf("Pressure\t%0.2f hPa\n", ((double) pressure) / 100);
	printf("Altitude\t%0.1f Feet\n", ((double) altitude) * 3.280839895);

	float q[4];
	while (1) {
		imu->getQ(q);
		printf("Q: %5.5f %5.5f %5.5f %5.5f\n", q[0], q[1], q[2], q[3]);
//		{
//			float x = mag->getX();
//			float y = mag->getY();
//			float z = mag->getZ();
//			float mag = sqrt(x * x + y * y + z * z);
//			x /= mag;
//			y /= mag;
//			z /= mag;
//
//			printf("MAG: %5.5f\t%5.5f\t%5.5f\n", x, y, z);
//		}
//		{
//			float x = gyro->getXRate();
//			float y = gyro->getYRate();
//			float z = gyro->getZRate();
//
//			printf("GYRO: %5.5f\t%5.5f\t%5.5f\n", x, y, z);
//		}
//		{
//			float x = acc->getX();
//			float y = acc->getY();
//			float z = acc->getZ();
//
//			printf("ACC: %5.5f\t%5.5f\t%5.5f\n", x, y, z);
//		}
	}

	delete bmp;
	delete gyro;

	return 0;
}
