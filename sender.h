/*
 * sender.h
 *
 *  Created on: 2012-07-02
 *      Author: mike
 */

#ifndef SENDER_H_
#define SENDER_H_

#include "comicFrames.h"
#include "mongoose/mongcpp.h"
#include <vector>

class Sender {
public:
	Sender() {}
	~Sender() {}

	void sendToClient(std::vector<ComicFrames>& frames, mongoose::MongooseResponse& response);
};


#endif /* SENDER_H_ */
