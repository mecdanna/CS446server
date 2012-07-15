#include "imageFactory.h"
#include "imageHeaders.h"
#include "lodepng/lodepng.h" // png processing
#include <cassert>
#include <fstream>

using namespace std;

void ImageFactory::FinalizePic(AbstractImage<pixel>& img) { }

ImageFactory::ImageFactory() { }

void ImageFactory::initPic(int w, int h, AbstractImage<pixel>& img, rawPic pic) { }

AbstractImage<pixel> _PNG(rawPic pic) {
	unsigned int w, h;
	unsigned char * image;
	lodepng_decode24_file(&image, &w, &h, pic);

	AbstractImage<pixel> result(w,h);
	for(int i = 0 ; i < w; i += 1 ) {
		for (int j = 0 ; j < h; j += 1) {
			result(i,j) = image[i*3 + i*j*3 + 0] << 24 |
					      image[i*3 + i*j*3 + 1] << 16 |
					      image[i*3 + i*j*3 + 2] << 8;
		}
	}
	return result;
}

AbstractImage<pixel> _BMP(rawPic pic) {
	AbstractImageHeader header = BmpHeader();
	istream * in = new ifstream(pic, ios::in | ios::binary);
	header.readHeader(*in);

	unsigned int w = header.getImageWidth();
	unsigned int h = header.getImageHeight();

	AbstractImage<pixel> result(w, h);
	in->seekg(h.getHeaderSize(), ios::beg);

	unsigned char pix[3];
	for( int i = 0; i < w; i += 1) {
		for( int j = 0; j < h; j += 1) {
			in->read(pix, sizeof(pix));
			result(i,j) = pix[0] << 24 | pix[1] << 16 | pix[2] << 8;
		}
	}
}

AbstractImage<pixel> _JPEG(rawPic pic) {

}

AbstractImage<pixel> ImageFactory::makeImage(rawPic pic, imageType type) {
	AbstractImage<pixel> result;

    switch( type ) {
        case imageType_PNG:
            result = _PNG(pic);
            break;
        case imageType_BMP:
            result = _BMP(pic);
            break;
        case imageType_JPEG:
            result = _JPEG(pic);
            break;
        default:
            assert(false);
    }

    return result;
}

ImageFactory::~ImageFactory() { }
