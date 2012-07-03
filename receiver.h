/*
 * receiver.h
 *
 *  Created on: 2012-07-02
 *      Author: mike
 */

#ifndef RECEIVER_H_
#define RECEIVER_H_

#include "HappyHttp/happyhttp.h"
#include "queue.h"
#include "httpStruct.h"

class Receiver {
	Queue& queue;

	bool checkForHttpRequest();

public:
	Receiver(Queue& queue) : queue(queue) {}
	void startListening();
};


#endif /* RECEIVER_H_ */
