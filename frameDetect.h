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

class FrameDetect {
	AbstractImage<pixel>& rimg;
	AbstractImage<byte> bimg;
	int page;
	byte ccolour; //contour colour
	byte bcolour; //background colour
	uint label;
	uint w, h;
protected:

    struct Point {
		uint x, y;
		Point(uint x, uint y): x(x), y(y) {}
		bool operator==(const Point& p) const { return x == p.x && y == p.y; }
    };

    inline static bool nextPoint(uint& x, uint& y, uint pos) {
		switch (pos)
		{
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

    inline bool nextPoint(uint& offset, uint pos) {
		switch (pos)
		{
			case 0: ++offset; break;
			case 1: offset += 1 + w; break;
			case 2: offset += w; break;
			case 3: offset += w-1; break;
			case 4: --offset; break;
			case 5: offset -= w+1; break;
			case 6: offset -= w; break;
			case 7: offset += w-1; break;
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
