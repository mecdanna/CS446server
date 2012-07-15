/*
 * receiver.h
 *
 *  Created on: 2012-07-02
 *      Author: mike
 */

#ifndef RECEIVER_H_
#define RECEIVER_H_

#include "queue.h"

class Receiver {
	Queue& queue;
	
protected:
  virtual bool handleEvent();
	
public:
	void start();
	void stop();
	Receiver(Queue& queue);
	~Receiver() {}
	
};


#endif /* RECEIVER_H_ */
