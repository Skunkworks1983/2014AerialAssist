/*
 FreeIMU.h - A libre and easy to use orientation sensing library for Arduino
 Copyright (C) 2011 Fabio Varesano <fabio at varesano dot net>

 Development of this code has been supported by the Department of Computer Science,
 Universita' degli Studi di Torino, Italy within the Piemonte Project
 http://www.piemonte.di.unito.it/


 This program is free software: you can redistribute it and/or modify
 it under the terms of the version 3 GNU General Public License as
 published by the Free Software Foundation.

 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.

 You should have received a copy of the GNU General Public License
 along with this program.  If not, see <http://www.gnu.org/licenses/>.

 */

#ifndef FreeIMU_h
#define FreeIMU_h

#define twoKpDef  (2.0f * 0.5f) // 2 * proportional gain
#define twoKiDef  (2.0f * 0.1f) // 2 * integral gain
#ifndef cbi
#define cbi(sfr, bit) (_SFR_BYTE(sfr) &= ~_BV(bit))
#endif

class BMP180;
class L3GD20;
class LSM303_ACC;
class LSM303_MAG;

class FreeIMU {
public:
	FreeIMU();
	void init();
	void init(bool fastmode);
	void init(int accgyro_addr, bool fastmode);
	void zeroGyro();
	void getRawValues(float * raw_values);
	void getValues(float * values);
	void getQ(float * q);
	void getEuler(float * angles);
	void getYawPitchRoll(float * ypr);
	void getEulerRad(float * angles);
	void getYawPitchRollRad(float * ypr);

	void gravityCompensateAcc(float * acc, float * q);

	float* raw_acc, raw_gyro, raw_magn;
	// calibration parameters
	float gyro_off_x, gyro_off_y, gyro_off_z;
	float acc_off_x, acc_off_y, acc_off_z, magn_off_x, magn_off_y, magn_off_z;
	float acc_scale_x, acc_scale_y, acc_scale_z, magn_scale_x, magn_scale_y,
			magn_scale_z;

	LSM303_ACC *acc;
	LSM303_MAG *mag;
	L3GD20 *gyro;
	BMP180 *baro;
private:
	void AHRSupdate(float gx, float gy, float gz, float ax, float ay, float az,
			float mx, float my, float mz);

	//float q0, q1, q2, q3; // quaternion elements representing the estimated orientation
	float iq0, iq1, iq2, iq3;
	float exInt, eyInt, ezInt;  // scaled integral error
	volatile float twoKp;      // 2 * proportional gain (Kp)
	volatile float twoKi;      // 2 * integral gain (Ki)
	volatile float q0, q1, q2, q3; // quaternion of sensor frame relative to auxiliary frame
	volatile float integralFBx, integralFBy, integralFBz;
	unsigned long lastUpdate, now; // sample period expressed in milliseconds
	float sampleFreq; // half the sample period expressed in seconds

	unsigned long startSeconds;
};

float invSqrt(float number);
void arr3_rad_to_deg(float * arr);

#endif // FreeIMU_h
