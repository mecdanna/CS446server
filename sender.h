/*
 * sender.h
 *
 *  Created on: 2012-07-02
 *      Author: mike
 */

#ifndef SENDER_H_
#define SENDER_H_

#include "HappyHttp/happyhttp.h"
#include "request.h"
#include <vector>

class Sender {
public:
	Sender();
	~Sender();

	void sendToClient(Request request, std::vector<ComicFrames> frames);
};


#endif /* SENDER_H_ */
