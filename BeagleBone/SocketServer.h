#ifndef SOCKETSERVER_H_
#define SOCKETSERVER_H_

#define BUFLEN 512
#define PORT 1180
#define SERVER_DEBUG_MODE 0

#include <pthread.h>

typedef void (*PacketHandler)(void *ptr, char *data);

/**
 * A TCP server that can accept at most a single client at a time, and broadcast the received messages through a function pointer to an external processor.
 */
class SocketServer {

public:
	/**
	 * Creates a generic SocketServer that can accept a single connection at a time.
	 * @param handler The function pointer to be called when a packet is received.  Can be NULL.
	 * @param inst The generic pointer to be passed to the packet handler.  Can be NULL.
	 */
	SocketServer(PacketHandler handler, void * inst);
	~SocketServer();

	// Send null-terminated string preferably < 512 bytes.
	int SendData(char *);

	// zero for for nothing new.
	bool Connected(); // Return connection status in case you're interested.

	void ClientConnect(); // Listen for client if we don't have one yet.
	// Has to be public so taskSpawn will work.
private:
	/**
	 * Copies buffer data into the given pointer, and returns the number of bytes read.
	 */
	int GetData(char *);

	/**
	 * The function pointer to a packet received callback;
	 */
	PacketHandler handler;
	/**
	 * The generic object to pass to the packet handler.
	 */
	void *handlerObj;
	/**
	 * Server socket; listens for connections.
	 */
	int listener;
	/**
	 * Single connected client.
	 */
	int connsock;
	/**
	 * The data buffer, with extra space for a null terminator.
	 */
	char data[BUFLEN + 1];
	/**
	 * Current length of data read into the buffer.
	 */
	int numbytes;

	/**
	 * Thread ID of the spawned read task.
	 */
	pthread_t tid;
	/**
	 * Thread attributes of the spawned read task.
	 */
	pthread_attr_t tAttr;
};

#endif
