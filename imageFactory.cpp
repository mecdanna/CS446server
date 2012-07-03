#include "imageFactory.h"

using namespace std;

void ImageFactory::FinalizePic(AbstractImage* img) {
}

ImageFactory::ImageFactory() {
}

void ImageFactory::_BMP(rawPic pic) {
}

void ImageFactory::_JPEG(rawPic pic) {
}

void ImageFactory::_PNG(rawPic pic) {
}

AbstractImage* ImageFactory::initPic(int w, int h) {
}

AbstractImage* ImageFactory::makeImage(rawPic pic, imageType type) {
}

ImageFactory::~ImageFactory() {
}

