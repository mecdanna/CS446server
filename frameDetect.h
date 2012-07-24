/*
 * frameDetect.h
 *
 *  Created on: 2012-07-02
 *      Author: mike
 */

#ifndef FRAMEDETECT_H_
#define FRAMEDETECT_H_

#include "abstractImage.h"
#include "comicFrames.h"

typedef AbstractImage<uint> LabelData;

/*
* This class detects all of the frames in a single page and returns them packaged.
* Very roughly, the algorithm works as follows:
* We binarize the image into background colour & a contour colour.
* We create a labelData bitmap, which tells you which pixel belongs to which frame.
* We then start filling it out by equating it to the label of the pixel that preceded it
* until we run  into an unhandled ccolour pixel, which we track and trace around, labelling them
* differently, before going back to filling the labels. Afterwards, we find bounding boxes for
* the labels, and return them as the frames.
*/
class FrameDetect {
	AbstractImage<pixel>& rimg;
	AbstractImage<byte> bimg;
	int page;
	byte ccolour; //contour colour (non-dominant binarized colour)
	byte bcolour; //background colour (dominant binarized colour)
	uint label;
	uint w, h;
protected:

    struct Point {
		uint x, y;
		Point(uint x, uint y): x(x), y(y) {}
		bool operator==(const Point& p) const { return x == p.x && y == p.y; }
    };

	/*
	 * used to find the next point while tracing a contour.Traces around a hexagon
	 * with an initial jump point (0) not being on the actual trace. 
	 */
    inline static bool nextPoint(uint& x, uint& y, uint pos) {
		switch (pos) {
			case 0: ++x; break;
			case 1: ++x; ++y; break;
			case 2: ++y; break;
			case 3: ++y; --x; break;
			case 4: --x; break;
			case 5: --x; --y; break;
			case 6: --y; break;
			case 7: ++x; --y; break;
			default:
					return false; break;

			return true;
		}
	}

	void addWhiteBorders();
    byte determineBackground(AbstractImage<byte>& img);
    void contourTracking(LabelData& labelData,uint x, uint y, uint initialPos, uint lbl);
    Point tracer(LabelData& labelData, uint x, uint y, uint pos, uint lbl);
    ComicFrames frames(LabelData& labelData) const;
    ComicFrames process(uint px, uint py, uint pw, uint ph);
public:

    FrameDetect(AbstractImage<pixel>& page, uint pageNum);
    ~FrameDetect();
    ComicFrames process();
};


#endif /* FRAMEDETECT_H_ */
