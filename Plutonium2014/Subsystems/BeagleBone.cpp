#include "BeagleBone.h"

#include "WPILib.h"
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <sys/socket.h>

#include "../Utils/Time.h"
#include "../Utils/Logger.h"

BeagleBone *BeagleBone::bone= NULL;

BeagleBone::BeagleBone() :
	Subsystem("BeagleBone") {
	BeagleBone::bone = this;
	listener = -1;
	connsock = -1;
	numbytes = 0;

	lastGyroUpdate = -1;
	lastVisionUpdate = -1;

	//	listen(listener, 1); // Listen for just one connection.

	if ((tid = taskSpawn("SocketComm", 100, 0, 10000,
			(FUNCPTR) BeagleBone::runTask, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0))
			== ERROR) {
		Logger::log(Logger::kSevere, "BeagleBone",
				"Failed to create listen thread.");
	}
}

BeagleBone::~BeagleBone() {
	taskDelete(tid); // Kill the waiting sockets.
	close(connsock);
	close(listener);
}

void BeagleBone::runTask() {
	if (bone!=NULL) {
		bone->ClientConnect();
	}
}

int BeagleBone::GetData(char *p) {
	strncpy(p, data, numbytes);
	p[numbytes]=0;
	int retbytes = numbytes;
	numbytes = 0; // Until we get new data.
	return retbytes;
}

// In case you want to send data back.  Note that you have to suspend
// the task in order to break the block on read().

int BeagleBone::SendData(char *p) {
	if (!Connected())
		return 0;
	taskSuspend(tid);
	int writ= write(connsock, p, strlen(p));
	taskResume(tid);
	return writ;
}

// Simplistic test for connected socket.

bool BeagleBone::Connected() {
	if (connsock == -1)
		return false;
	return true;
}

void BeagleBone::ClientConnect() {
	while (1) {
		Logger::log(Logger::kFinest, "BeagleBone", "Beginning Read Thread");
		if ((connsock = socket(AF_INET, SOCK_STREAM, 0)) == -1) { // Should never fail.
			cout<<"Server listener create Error"<<endl;
			return;
		}

		struct sockaddr_in sin;
		memset((char *) &sin, 0, sizeof(sin));
		memset(&sin, 0, sizeof(sin));
		sin.sin_family = AF_INET;
		sin.sin_port = htons(PORT);
		sin.sin_addr.s_addr = inet_addr("10.19.83.5");

		while (1) {
			// bind can fail if socket is still out there listening.
			// This scenario happens when loading new code without reboot.
			if (connect(connsock, (struct sockaddr *) &sin, sizeof(sin)) == -1) {
				Wait(10.0);
				continue;
			} else {
				break;
			}
		}
		Logger::log(Logger::kInfo, "BeagleBone", "Connected!");

		while (connsock != -1) {
			int ret = read(connsock, data, BUFLEN);

			if (ret < 0) {
				connsock = -1;
			} else if (ret == 0) // Other end hung up.
			{
				close(connsock);
				connsock = -1;
			} else {
				data[ret]=0;
				numbytes = ret;
				char * p = new char[numbytes];
				if (GetData(p) > 0) {
					parse(p);
				}
			}
		}
	}
}

void BeagleBone::parse(char *data) {
	int area;
	float x, y, level1, level2;
	int id, total;
	double time = getCurrentMillis();
	sscanf(data, "%d/%d\t%d\t%f\t%f\t%f\t%f", &id, &total, &area, &x, &y,
			&level1, &level2);

	if (id == 1337 && total == 1337) {
		//Gyro
		gyro.yaw = y;
		gyro.pitch = level1;
		gyro.roll = level2;
		lastGyroUpdate = time;
	} else {
		vision.x = x;
		vision.y = y;
		vision.level1 = level1;
		vision.level2 = level2;
		vision.id = id;
		vision.total = total;
		vision.area = area;
		lastVisionUpdate = time;
	}
}

bool BeagleBone::isGyroActive() {
	return lastGyroUpdate + 5000 > getCurrentMillis();
}

