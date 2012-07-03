#include "imagePreprocessor.h"

using namespace std;

ImagePreprocessor::ImagePreprocessor(rawData data, ImagePreprocessor::decompressType type, std::vector<AbstractImage>& images) :
	images(images) {
}

void ImagePreprocessor::_CBR(rawData data) {
}

void ImagePreprocessor::_CBZ(rawData data) {
}

ImagePreprocessor::~ImagePreprocessor() {
}

