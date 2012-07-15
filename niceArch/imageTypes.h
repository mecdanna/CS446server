#ifndef IMAGE_TYPES_H
#define IMAGE_TYPES_H

#include "imageHeaders.h"
#include <istream>

class AbstractImageType {
  protected:
    AbstractImageHeader * header = 0;

  public:
    virtual unsigned int getPixel() = 0;
    virtual unsigned int getWidth(); 
    virtual unsigned int getHeight(); 
    virtual unsigned int readImage(std::istream& rawPic);
    virtual unsigned int readImage(rawPicInMem rawPic);
}

class BmpImageType : public AbstractImageType;
class JpgImageType : public AbstractImageType;
class PngImageType : public AbstractImageType;

/*
class BmpImageType : public AbstractImageType {
    unsigned int readImage(std::istream& rawPic);
    unsigned int readImage(rawPicInMem rawPic);
    unsigned int getPixel();
} 

class PngImageType : public AbstractImageType {
    unsigned int readImage(std::istream& rawPic);
    unsigned int readImage(rawPicInMem rawPic);
    unsigned int getPixel();
}

class JpgImageType : public AbstractImageType {
    unsigned int getWidth(); 
    unsigned int getHeight(); 
    unsigned int readImage(std::istream& rawPic);
    unsigned int readImage(rawPicInMem rawPic);
    unsigned int getPixel();
}
*/

#endif
