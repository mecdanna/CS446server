#include "frameDetect.h"
#include "comicFrames.h"

using namespace std;

FrameDetect::FrameDetect(AbstractImage<pixel>& page, int pageNum) : rimg(page) {
	bimg = rimg.binarize(228);
	bcolour = determineBackground(bimg);
	ccolour = 255 - bcolour;
	FrameDetect::page = pageNum;
	
	addWhiteBorders();
	
	w = page.width();
	h = page.height();
}

FrameDetect::~FrameDetect() {}


ComicFrames FrameDetect::process() {
	return process(1, 1, w, h-1);
}

void FrameDetect::contourTracking(LabelData& labelData, int x, int y, int initialPos, int lbl) {
	int c = initialPos;
	Point s(x, y);
	
	bool atStart = false; //gotten back to initial position
	bool nFollowsS = false; //ahead of initial position (circled around)
	
	Point n = tracer(labelData, x, y, c, lbl);
	if (n.x < 0) { //isolated point
		return;
	}
	
	labelData(n.x, n.y) = lbl;
	x = n.x;
	y = n.y;
	
	while(!atStart || !nFollowsS) {
		c = (c + 6) % 8; //previous contour is d+4, next initial position is d+2
		
		const Point f(tracer(labelData, x, y, c, lbl));
		
		if (f.x < 0) { //image boundary
			return;
		}
		
		if (f == s) {
			atStart = true;
		} else if (f == n) {
			if (atStart) {
				nFollowsS = true;
			}
		} else {
			atStart = nFollowsS = false;
		}
		
		labelData(f.x, f.y) = lbl;

		x = f.x;
		y = f.y;
	}
}

FrameDetect::Point FrameDetect::tracer(LabelData& labelData, int x, int y, int pos, int lbl) {
	for (int i = 7; i >= 0; --i) {
		int tx = x;
		int ty = y;
		nextPoint(tx, ty, pos);
		
		if (tx > 0 && ty > 0 && tx < w && ty < h) {
			const int &l = labelData(tx,ty);
			
			if (bimg.at(tx,ty) == ccolour && (l == 0 || l == lbl))
			{
				return Point(tx,ty);
			}
			if (bimg.at(tx,ty) == bcolour)
			{
				labelData(tx,ty) = -1;
			}
		}
		
		pos = (pos + 1) % 8;
	}
	return Point(-1, -1);
}

ComicFrames FrameDetect::frames(LabelData& labelData) const {
	vector<int> x1(label);
	vector<int> x2(label);
	vector<int> y1(label);
	vector<int> y2(label);
	
	//initialize tables
	for (int lbl=0; lbl<label; lbl++) {
		x1[lbl] = w;
		x2[lbl] = y2[lbl] = -1;
		y1[lbl] = h;
	}
	
	//find bounding boxes for labels
	for (int y = 0; y < h; ++y) {
		for (int x = 0; x < w; ++x) {
			
			int lbl = labelData(x, y);
			
			if (lbl > 0) {
				if (x < x1[lbl]) { x1[lbl] = x; }
				if (x > x2[lbl]) { x2[lbl] = x; }
				if (y < y1[lbl]) { y1[lbl] = y; }
				if (y > y2[lbl]) { y2[lbl] = y; }
			}
		}
	}
	
	ComicFrames comicFrames(page, w, h);
	
	for (int lbl = 0; lbl < label; ++lbl) {
		int FW = x2[lbl]-x1[lbl];
		int FH = y2[lbl]-y1[lbl];
		
		if ((FW >= w/6) && (FH >= h/8)) {
			comicFrames.append(comicFrame(x1[lbl], y1[lbl], w, h, lbl));
		}
	}
	
	//No frames, use image
	if (comicFrames.count() == 0) {
		comicFrames.append(comicFrame(0, 0, w, h, 0));
	}
	return comicFrames;
}

ComicFrames FrameDetect::process(int px, int py, int pw, int ph) {
	LabelData labelData(w, h); //allocates more than required
	labelData.fill(0);
	
	label = 1;
	for(int y = py; y < py + ph; ++y) {
		for (int x = px; x < px + pw; ++x) {
			int p = labelData(x,y);
			
			if (bimg.at(x,y) == ccolour) { //find contour pixel
			//step 1
				if (p == 0 && bimg.at(x,y-1) == bcolour) {
					p = label;
					contourTracking(labelData, x, y, 7, label++);
					
				} else if (labelData.at(x,y+1) == 0 && bimg.at(x,y+1) == bcolour) { //pixel is below unmarked pixel
			//step 2
					if (p == 0) {
						p = labelData.at(x-1, y); //copy label
					}
					contourTracking(labelData, x, y, 3, p);
					
				} else if (p == 0) {
					p = labelData(x-1,y);
				}
			}
		}
	}
	
	return frames(labelData);
}

void FrameDetect::addWhiteBorders() {
	for(int x = 0; x < w-1; ++x) {
		bimg.at(x,0) = bimg.at(x,h-1) = bcolour;
	}
	
	for(int y = 0; y < h-1; ++y) {
		bimg.at(0,y) = bimg.at(w-1,y) = bcolour;
	}
}

int FrameDetect::determineBackground(AbstractImage<byte>& img) {
	int stripWidth = w/100;
	
	int black = 0;
	int white = 0;
	
	for(int y = 0; y < h; ++y) {
		for(int x = 0; x < stripWidth; ++x) {
			if(img(x,y) == 0) {
				++black;
			} else {
				++white;
			}
			
			if(img(w-x-1, y) == 0) {
				++black;
			} else {
				++white;
			}
		}
	}
	
	return black > white ? 255: 0;
}
