/*
 * frameDetect.h
 *
 *  Created on: 2012-07-02
 *      Author: mike
 */

#ifndef FRAMEDETECT_H_
#define FRAMEDETECT_H_

#include "abstractImage.h"
#include "binarizedImage.h"
#include "comicFrames.h"

class FrameDetect {
	BinarizedImage* bimg;
	int page;
	int ccolour; //contour colour
	int bcolour; //background colour
	int label;
	int w, h;
protected:

    struct Point {
		int x, y;
		Point(int x, int y): x(x), y(y) {}
		bool operator==(const Point& p) const { return x == p.x && y == p.y; }
    };

    void addWhiteBorders();
    static int determineBackground(const BinarizedImage &img);

    inline static bool nextPoint(int& x, int& y, int pos) {
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

    inline bool nextPoint(int& offset, int pos) {
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

    void contourTracking(AbstractImage* img, int x, int y, int initialPos, int label);
    Point tracer(AbstractImage* img, int x, int y, int pos, int label);
    ComicFrames frames(AbstractImage* img) const;
    ComicFrames process(int px, int py, int pw, int ph);
public:

    FrameDetect(const AbstractImage &page);
    ~FrameDetect();
    ComicFrames process();
    void dump(const AbstractImage* img);

};


#endif /* FRAMEDETECT_H_ */
