#include "frameDetect.h"

using namespace std;

FrameDetect::FrameDetect(const AbstractImage &page) {
	
}

FrameDetect::~FrameDetect() {
	
}

ComicFrames process() {
	
}

void FrameDetect::dump(const AbstractImage* img) {
	
}

void FrameDetect::contourTracking(AbstractImage* img, int x, int y, int initialPos, int label) {
	
}

FrameDetect::Point FrameDetect::tracer(AbstractImage* img, int x, int y, int pos, int label) {
	
}

ComicFrames FrameDetect::frames(AbstractImage* img) const {
	
}

ComicFrames FrameDetect::process(int px, int py, int pw, int ph) {
	
}

void FrameDetect::addWhiteBorders() {
	
}

int FrameDetect::determineBackground(const BinarizedImage &img) {
	
}
