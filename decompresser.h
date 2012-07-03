/*
 * decompresser.h
 *
 *  Created on: 2012-07-02
 *      Author: mike
 */

#ifndef DECOMPRESSER_H_
#define DECOMPRESSER_H_

#include <list>
#include <vector>
#include "abstractImage.h"

class Decompresser {
	std::vector<AbstractImage> images;

	void _CBR(void* data);
	void _CBZ(void* data);

public:
	enum decompressType {
		decompressType_CBR = 0,
		decompressType_CBZ
	};
	Decompresser(void* data, decompressType type);
	~Decompresser();

	std::vector<AbstractImage>* getImages() {return &images;}

};


#endif /* DECOMPRESSER_H_ */
