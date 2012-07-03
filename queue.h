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
#include "httpStruct.h"

class Queue {
	queue<void*> m_dataQueue;
	queue<HttpStruct> m_HttpQueue;
	pthread_rwlock_t m_mutex;


public:
	void enqueue(void* data);
	void* dequeue();
};


#endif /* QUEUE_H_ */
