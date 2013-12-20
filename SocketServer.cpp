#include "SocketServer.h"

#include <stdio.h>
#include <iostream>
#include <unistd.h>
#include <string.h>

#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <sys/socket.h>

#include <pthread.h>
#include <signal.h>

using namespace std;

void* doblocked(void *arg) {
	((SocketServer*) arg)->ClientConnect(); // Never leaves.
	return NULL;
}

SocketServer::SocketServer(PacketHandler tHandler, void * ptr) {
	handlerObj = ptr;
	handler = tHandler;
	listener = -1;
	connsock = -1;
	numbytes = 0;

	if ((listener = socket(AF_INET, SOCK_STREAM, 0)) == -1) { // Should never fail.
#if SERVER_DEBUG_MODE
			cerr << "Server listener create Error" << endl;
#endif
		return;
	}

	struct sockaddr_in sin;
	memset((char *) &sin, 0, sizeof(sin));
	sin.sin_family = AF_INET;
	memset(&sin, 0, sizeof(sin));
	sin.sin_family = AF_INET;
	sin.sin_port = htons(PORT);
	sin.sin_addr.s_addr = htonl(INADDR_ANY );

	int one;
	setsockopt(listener, SOL_SOCKET, SO_REUSEADDR, (char *) &one, sizeof(one));

	if (bind(listener, (struct sockaddr *) &sin, sizeof(sin)) == -1) {
#if SERVER_DEBUG_MODE
		cerr << "Bind failed.  Likely another socket is already listening." << endl;
#endif
		return;
	}

	listen(listener, 1); // Listen for just one connection.
	pthread_attr_init(&tAttr);
	if (pthread_create(&tid, &tAttr, doblocked, this) != 0) {
#if SERVER_DEBUG_MODE
		cerr << "Task creation error pthreads" << endl;
#endif
	}
}

SocketServer::~SocketServer() {
	pthread_cancel(tid); // Kill the waiting sockets.
	close(connsock);
	close(listener);
}

int SocketServer::GetData(char *p) {
	strncpy(p, data, numbytes);
	p[numbytes] = 0;
	int retbytes = numbytes;
	numbytes = 0; // Until we get new data.
	return retbytes;
}

int SocketServer::SendData(char *p) {
	if (!Connected()) {
		return 0;
	}
	pthread_kill(tid, SIGUSR1); // Interrupt the read() call.
	int writ = write(connsock, p, strlen(p));
	return writ;
}

bool SocketServer::Connected() {
	if (connsock == -1)
		return false;
	return true;
}

void handleUserSignal(int sig) {
	signal(SIGSEGV, handleUserSignal);
}

void SocketServer::ClientConnect() {
	signal(SIGUSR1, handleUserSignal);

	while (1) {
		if (connsock == -1) {
			struct sockaddr remoteaddr;
			unsigned int rsize = sizeof(remoteaddr);
			connsock = accept(listener, &remoteaddr, &rsize);
		} else {
			int ret = read(connsock, data, BUFLEN);

			if (ret < 0) {
				connsock = -1;
			} else if (ret == 0) {
				close(connsock);
				connsock = -1;
			} else {
				data[ret] = 0;
#if SERVER_DEBUG_MODE
				cerr << "Got " << ret << " bytes: " << data << endl;
#endif
				numbytes = ret;

				if (handler != NULL) {
					char * p = new char[numbytes];
					if (GetData(p) > 0) {
						handler(handlerObj, p);
					}
				}
			}
		}
	}
	return;
}

