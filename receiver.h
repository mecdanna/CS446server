/*
 * receiver.h
 *
 *  Created on: 2012-07-02
 *      Author: mike
 */

#ifndef RECEIVER_H_
#define RECEIVER_H_

#include "queue.h"

/*
 * This class receives http requests and enqueues them. It is not
 * explicitly a singleton, but multiple receivers will interfere
 * with each other if they run on the same port.
 */
class Receiver {
	int httpd;
	static bool done;
	pthread_t thread;
	
protected:
	static void handleEvent(int clientSocket);
	static void* process(void* params);
	
public:
	void start();
	void stop();
	Receiver(unsigned short port);
	~Receiver() {}
	
};


#endif /* RECEIVER_H_ */
