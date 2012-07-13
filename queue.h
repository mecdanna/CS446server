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

typedef void* rawData;

class Queue {
	std::queue<rawData> m_dataQueue;
	pthread_rwlock_t m_mutex;


public:
	void enqueue(rawData data);
	void* dequeue();
};


#endif /* QUEUE_H_ */
