/*
 * decompresser.h
 *
 *  Created on: 2012-07-02
 *      Author: mike
 */

#ifndef IMAGEPREPROCESSOR_H_
#define IMAGEPREPROCESSOR_H_

#include <list>
#include <vector>
#include "abstractImage.h"

typedef void* rawData;

class ImagePreprocessor {
	std::vector<AbstractImage>& images;

	void _CBR(void* data);
	void _CBZ(void* data);

public:
	enum decompressType {
		decompressType_CBR = 0,
		decompressType_CBZ
	};
	ImagePreprocessor(rawData data, decompressType type);
	~ImagePreprocessor();

	std::vector<AbstractImage>* getImages() {return images;}

};


#endif /* IMAGEPREPROCESSOR_H_ */
