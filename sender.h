/*
 * sender.h
 *
 *  Created on: 2012-07-02
 *      Author: mike
 */

#ifndef SENDER_H_
#define SENDER_H_

#include "comicFrames.h"
#include <vector>

typedef int response;

class Sender {
public:
	Sender() {}
	~Sender() {}

	void sendToClient(std::vector<ComicFrames>& frames, response& res);
};


#endif /* SENDER_H_ */
