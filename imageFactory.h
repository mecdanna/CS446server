 /*
 * imageFactory.h
 *
 *  Created on: 2012-07-03
 *      Author: mike
 */
 
#ifndef IMAGEFACTORY_H_
#define IMAGEFACTORY_H_

#include "abstractImage.h"

typedef void* rawPic;

class ImageFactory {
	_PNG(rawPic pic);
	_BMP(rawPic pic);
	_JPEG(rawPic pic);
	
	AbstractImage* initPic(int w, int h);
	void FinalizePic(AbstractImage* img);
public:
	enum imageType {
		imageType_PNG = 0,
		imageType_BMP,
		imageType_JPEG
	}
	ImageFactory();
	~ImageFactory();
	
	AbstractImage* makeImage(rawPic pic, imageType type);
};


#endif /* IMAGEFACTORY_H_ */
 