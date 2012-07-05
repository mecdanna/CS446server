#include "imageFactory.h"

using namespace std;

void ImageFactory::FinalizePic(AbstractImage<pixel>& img) {
}

ImageFactory::ImageFactory() {
}

void ImageFactory::_BMP(rawPic pic) {
}

void ImageFactory::_JPEG(rawPic pic) {
}

void ImageFactory::_PNG(rawPic pic) {
}

void ImageFactory::initPic(int w, int h, AbstractImage<pixel>& img) {
}

AbstractImage<pixel> ImageFactory::makeImage(rawPic pic, imageType type) {
}

ImageFactory::~ImageFactory() {
}

