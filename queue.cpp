#include "queue.h"

using namespace std;
using namespace mongoose;

rawData Queue::dequeue(size_t &size, MongooseResponse& response) {
	size = m_size.front(); m_size.pop();
	response = *m_response.front(); m_response.pop();
	rawData t = m_dataQueue.front(); m_dataQueue.pop();
	return t;
}

void Queue::enqueue(rawData data, size_t size, MongooseResponse& response) {
	m_dataQueue.push(data);
	m_size.push(size);
	m_response.push(&response);
}

