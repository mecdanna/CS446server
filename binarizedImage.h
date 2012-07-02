/*
 * binarizeImage.h
 *
 *  Created on: 2012-07-02
 *      Author: mike
 */

#ifndef BINARIZEDIMAGE_H_
#define BINARIZEDIMAGE_H_

#include "abstractImage.h"

class BinarizedImage: public AbstractImage {
public:
	BinarizedImage(const AbstractImage &img, int thmin);
	void invert();

	AbstractImage toImage() { return (AbstractImage)*self;}
};


#endif /* BINARIZEDIMAGE_H_ */
