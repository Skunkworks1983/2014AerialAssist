/*
 * L3GD20.h
 *
 *  Created on: Feb 6, 2014
 *      Author: lwestin
 */

#ifndef L3GD20_H_
#define L3GD20_H_

#include "internal/I2C.h"

#define L3GD20_ADDR (0x6B)
// CONTROL REGISTERS
#define L3GD20_CTREG1 (0x20)
#define L3GD20_CTREG4 (0x23)
// CONTROL VALUES
#define L3GD20_ON (0x0F)
#define L3GD20_DPS250 (0x00)
#define L3GD20_DPS500 (0x10)
#define L3GD20_DPS2000 (0x20)
// DATA OUTPUTS
#define L3GD20_XOUTLOW (0x28)
#define L3GD20_XOUTHIGH (0x29)
#define L3GD20_YOUTLOW (0x2A)
#define L3GD20_YOUTHIGH (0x2B)
#define L3GD20_ZOUTLOW (0x2C)
#define L3GD20_ZOUTHIGH (0x2D)

class L3GD20: public I2C {
public:
	enum Resolution {
		DPS_250, DPS_500, DPS_2000
	};
private:
	Resolution res;
	float scalingValue;
	float naturalX, naturalY, naturalZ;
	float getRate(int lowAddr, int highAddr);
public:
	L3GD20();
	virtual ~L3GD20();

	void calibrate(Resolution res = DPS_250);

	inline float getXRate() {
		return getRate(L3GD20_XOUTLOW, L3GD20_XOUTHIGH) - naturalX;
	}
	inline float getYRate() {
		return getRate(L3GD20_YOUTLOW, L3GD20_YOUTHIGH) - naturalY;
	}
	inline float getZRate() {
		return getRate(L3GD20_ZOUTLOW, L3GD20_ZOUTHIGH) - naturalZ;
	}
};

#endif /* L3GD20_H_ */
