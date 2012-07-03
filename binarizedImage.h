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
	void binarize();
	
public:
	BinarizedImage(const AbstractImage& img, int thmin = 228);
	void invert();

	AbstractImage toImage() { return (AbstractImage)*this;}
};


#endif /* BINARIZEDIMAGE_H_ */
