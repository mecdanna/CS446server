/*
 * receiver.h
 *
 *  Created on: 2012-07-02
 *      Author: mike
 */

#ifndef RECEIVER_H_
#define RECEIVER_H_

#include "queue.h"
#include "mongoose/mongcpp.h"

class Receiver : public mongoose::MongooseServer {
	Queue& queue;
	
	void addToQueue();
	
protected:
  virtual bool handleEvent(mongoose::ServerHandlingEvent eventCode, mongoose::MongooseConnection &connection, const mongoose::MongooseRequest &request, mongoose::MongooseResponse &response);
	
public:
	Receiver(Queue& queue);
	~Receiver();
	
};


#endif /* RECEIVER_H_ */
