#ifndef __BEAGLEBONE_H
#define __BEAGLEBONE_H
#include "Commands/Subsystem.h"

#define BUFLEN 512
#define PORT 1180
class BeagleBone : public Subsystem {
public:
	typedef struct {
		int area;
		float x, y, level1, level2;
		int id, total;
	} VisionState;
	typedef struct {
		float yaw, pitch, roll;
	} GyroState;
private:
	int listener; // Our listening socket.
	int connsock; // Our connected client.  Just one.
	char data[BUFLEN+1]; // Leave space for a null, always.
	int numbytes; // Number of bytes to copy in when GetData called.
	int tid; // Spawned task id, needed to suspend when writing

	int SendData(char *); // Send null-terminated string preferably < 512 bytes.
	int GetData(char *); // Return number of bytes copied into pointer, 
	// zero for for nothing new.

	void ClientConnect(); // Listen for client if we don't have one yet. 
	// Has to be public so taskSpawn will work.

	void parse(char *data);

public:
	bool Connected(); // Return connection status in case you're interested.

	// State params
	GyroState gyro;
	double lastGyroUpdate;
	VisionState vision;
	double lastVisionUpdate;

	bool isGyroActive();

	static BeagleBone *bone;
	static void runTask();

	BeagleBone();
	~BeagleBone();
};

#endif
