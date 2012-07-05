/*
 * worker.h
 *
 *  Created on: 2012-07-02
 *      Author: mike
 */

#ifndef WORKER_H_
#define WORKER_H_

#include "frameDetect.h"
#include "comicFrames.h"
#include "sender.h"
#include "queue.h"
#include <vector>

class Worker {
	Queue& m_queue;
	
	std::vector<AbstractImage<pixel> > pages;

public:
	void process();
	Worker(Queue& queue) : m_queue(queue){}
	~Worker();
};


#endif /* WORKER_H_ */
