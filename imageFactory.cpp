#include "imageFactory.h"
#include "imageHeaders.h"
#include "lodepng/lodepng.h" // png processing
#include <cassert>
#include <fstream>

using namespace std;

void ImageFactory::FinalizePic(AbstractImage<pixel>& img) { }

ImageFactory::ImageFactory() { }

void ImageFactory::initPic(int w, int h, AbstractImage<pixel>& img, rawPic pic) { }

AbstractImage<pixel> ImageFactory::_PNG(rawPic pic) {
	unsigned int w, h;
	unsigned char * image;
	lodepng_decode24_file(&image, &w, &h, pic);

	AbstractImage<pixel> result(w,h);
	for(int i = 0 ; i < w; i += 1 ) {
		for (int j = 0 ; j < h; j += 1) {
			result.at(i,j) = image[j*w*3 + i*3 + 0] << 8 |
					         image[j*w*3 + i*3 + 1] << 16 |
					         image[j*w*3 + i*3 + 2] << 24;
		}
	}
	return result;
}

AbstractImage<pixel> ImageFactory::_BMP(rawPic pic) {
	BmpHeader header = BmpHeader();
	istream * in = new ifstream(pic, ios::in | ios::binary);
	header.readHeader(*in);

	unsigned int w = header.getImageWidth();
	unsigned int h = header.getImageHeight();

	AbstractImage<pixel> result(w, h);

    unsigned int rowSize = w*3;         // 3 bytes per pixel * width
    unsigned int padding = (4 - (rowSize % 4)) % 4;
    rowSize = rowSize + padding;  // account for padding

    in->seekg(0, ios::end);
    unsigned int end = in->tellg();

	unsigned char pixel[3];

    for( int j = 0; j < h; j += 1) {
        in->seekg(end - (j*rowSize + rowSize));
        for( int i = 0; i < w; i += 1) {
			in->read((char*)pixel, sizeof(pixel));
			result.at(i,j) = pixel[0] << 24 | pixel[1] << 16 | pixel[2] << 8;
		}
	}

    return result;
}

AbstractImage<pixel> ImageFactory::_JPEG(rawPic pic) {

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
