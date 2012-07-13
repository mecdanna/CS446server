#include "queue.h"

using namespace std;
using namespace mongoose;

Queue::Queue() : m_mutex(PTHREAD_MUTEX_INITIALIZER) {}

rawData Queue::dequeue(size_t &size, MongooseResponse& response) {
	pthread_mutex_lock(&m_mutex);
		size = m_size.front(); m_size.pop();
		response = *m_response.front(); m_response.pop();
		rawData t = m_dataQueue.front(); m_dataQueue.pop();
		pthread_mutex_unlock(&m_mutex);
	return t;
}

void Queue::enqueue(rawData data, size_t size, MongooseResponse& response) {
	pthread_mutex_lock(&m_mutex);
		m_dataQueue.push(data);
		m_size.push(size);
		m_response.push(&response);
	pthread_mutex_unlock(&m_mutex);
}

