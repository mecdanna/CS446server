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
	void _PNG(rawPic pic);
	void _BMP(rawPic pic);
	void _JPEG(rawPic pic);
	
	void initPic(int w, int h, AbstractImage<pixel>& img, rawPic pic);
	void FinalizePic(AbstractImage<pixel>& img);
public:
	enum imageType {
		imageType_PNG = 0,
		imageType_BMP,
		imageType_JPEG
	};
	ImageFactory();
	~ImageFactory();
	
	AbstractImage<pixel> makeImage(rawPic pic, imageType type);
};


#endif /* IMAGEFACTORY_H_ */
 