/*
 * queue.h
 *
 *  Created on: 2012-07-02
 *      Author: mike
 */

#ifndef QUEUE_H_
#define QUEUE_H_

#include <queue>
#include <pthread.h>
#include "mongoose/mongcpp.h"

typedef void* rawData;

class Queue {
	std::queue<rawData> m_dataQueue;
	std::queue<size_t> m_size;
	std::queue<mongoose::MongooseResponse*> m_response;
	pthread_mutex_t m_mutex;


public:
	Queue();
	~Queue() {}

	void enqueue(rawData data, size_t size, mongoose::MongooseResponse &response);
	rawData dequeue(size_t &size, mongoose::MongooseResponse &response);
};


#endif /* QUEUE_H_ */
