#include "abstractImage.h"
#include "imageHeaders.h"
#include "lodepng/lodepng.h"
#include "imagePreprocessor.h"
#include "frameDetect.h"
#include "comicFrames.h"
#include <fstream>
#include <istream>
#include <cstdint>
#include <iostream>
#include <iomanip>

using namespace std;

typedef char* rawPic;

void PNG(rawPic pic) {
// AbstractImage<pixel> PNG(rawPic pic) {
	unsigned int w, h;
	unsigned char * image;
	lodepng_decode24_file(&image, &w, &h, pic);

    cout << hex;

	//AbstractImage<pixel> result(w,h);
    for (int j = 0 ; j < h; j += 1) {
        for(int i = 0 ; i < w; i += 1 ) {
            cout << setw(2) << setfill('0') << (unsigned int)image[j*w*3 + i*3 + 0];
            cout << setw(2) << setfill('0') << (unsigned int)image[j*w*3 + i*3 + 1];
            cout << setw(2) << setfill('0') << (unsigned int)image[j*w*3 + i*3 + 2] << " ";
            //cout << setw(8) << setfill('0') << (unsigned int)(image[i*3 + i*j*3 + 0] << 24 | image[i*3 + i*j*3 + 1] << 16 | image[i*3 + i*j*3 + 2] << 8) << " ";
			//result(i,j) = image[i*3 + i*j*3 + 0] << 24 |
		    //			      image[i*3 + i*j*3 + 1] << 16 |
		    //			      image[i*3 + i*j*3 + 2] << 8;
		}
        cout << endl;
	}

    delete [] image;
//	return result;
}

//AbstractImage<pixel> BMP(rawPic pic) {
void BMP(rawPic pic) {
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

    cout << hex;

	unsigned char pixel[3];
    // in->read((char *)pixels, rowSize*h);

    for( int j = 0; j < h; j += 1) {
        in->seekg(end - (j*rowSize + rowSize));
        for( int i = 0; i < w; i += 1) {
			in->read((char*)pixel, sizeof(pixel));
			result(i,j) = pixel[0] << 24 | pixel[1] << 16 | pixel[2] << 8;
            cout << setw(2) << setfill('0') << (unsigned int)pixel[0];
            cout << setw(2) << setfill('0') << (unsigned int)pixel[1];
            cout << setw(2) << setfill('0') << (unsigned int)pixel[2] << " ";
		}
        cout << endl;
	}

    // delete [] pixels;
}


int main() {
//    AbstractImage<pixel> bmp = BMP("test.bmp"); 
    //AbstractImage<pixel> png = PNG("test.png"); 
//    PNG("ulx0.5_cover.png"); 
//
    vector< AbstractImage<pixel> > images;
    ImagePreprocessor p = ImagePreprocessor("test.cbz", ImagePreprocessor::decompressType_CBZ, images);

    for ( int i = 0; i < images.size(); i += 1 ) {
        FrameDetect f = FrameDetect(images[i], i);
        ComicFrames cfs = f.process();
        cout << "Comic Frames for page: " << i << endl;
        for( int k = 0; k < cfs.count(); k += 1 ) {
            //cout << "    Frame " << k << ": (" << cfs[k].xPos() << " , " << cfs[k].yPos() << ") - " << cfs[k].width() << "x" << cfs[k].height() << endl;
            cout << "    Frame " << k << ":" << endl;
        }
    }

    return 0;
}
