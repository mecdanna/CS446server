 /*
 * imageFactory.h
 *
 *  Created on: 2012-07-03
 *      Author: mike
 */
 
#ifndef IMAGEFACTORY_H_
#define IMAGEFACTORY_H_

#include "abstractImage.h"

typedef char* rawPic; // file path to pic

class ImageFactory {
	void initPic(int w, int h, AbstractImage<pixel>& img, rawPic pic);
	void FinalizePic(AbstractImage<pixel>& img);
	AbstractImage<pixel> _PNG(rawPic pic);
	AbstractImage<pixel> _BMP(rawPic pic);
	AbstractImage<pixel> _JPEG(rawPic pic);
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
