/*
 * I2CBus.h
 *
 *  Created on: Feb 6, 2014
 *      Author: lwestin
 */

#ifndef I2CBUS_H_
#define I2CBUS_H_

class I2CBus {
private:
	static int fd;
	static int references;
	I2CBus();
	virtual ~I2CBus();
public:
	static void allocateFD();
	inline static int getFD() {
		return fd;
	}
	static void freeFD();
};

#endif /* I2CBUS_H_ */
