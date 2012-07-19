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

typedef unsigned char* rawData;
typedef int response;

class Queue {
	std::queue<rawData> m_dataQueue;
	std::queue<size_t> m_size;
	std::queue<response> m_response;
	pthread_mutex_t m_mutex;

	static Queue* q;
public:
	Queue();
	~Queue() {}

	static Queue* getQueue() { return q;}
	void enqueue(rawData data, size_t size, response& res);
	rawData dequeue(size_t& size, response& res);
};


#endif /* QUEUE_H_ */
