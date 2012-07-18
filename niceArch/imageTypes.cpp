#include "imageTypes.h"
#include "lodepng/lodepng.h" // for png processing

using namespace std;

unsigned int AbstractImageType::getWidth() {
    if (header == 0) return 0;
    return header->getWidth(); 
}

unsigned int AbstractImageType::getWidth() {
    if (header == 0) return 0;
    return header->getHeight(); 
}

unsigned int AbstractImageType::readImage(std::istream& rawPic) {
}

unsigned int AbstractImageType::readImage(rawPicInMem rawPic) {

}
