/*
 * comicFrames.h
 *
 *  Created on: 2012-07-02
 *      Author: mike
 */

#ifndef COMICFRAMES_H_
#define COMICFRAMES_H_

#include <vector>

typedef unsigned int uint;

//Contains all of the information for a single frame in a page
struct comicFrame {
	comicFrame() {}
	comicFrame(uint x, uint y, uint w, uint h, uint label) : x(x), y(y), w(w), h(h), lbl(label) {}

	uint width() {return w;}
	uint height() {return h;}
	uint xPos() {return x;}
	uint yPos() {return y;}
	uint label() {return lbl;}

private:
	uint x, y, w, h, lbl;
};

//Contains all of the frames for a single page.
class ComicFrames {
	uint m_page;
	uint m_pageWidth;
	uint m_pageHeight;
	std::vector<comicFrame> m_frames;
public:
	ComicFrames(uint page = -1, uint width = 0, uint height = 0) : m_page(page), m_pageWidth(width), m_pageHeight(height) {}
	~ComicFrames() { m_frames.clear(); }

	void append(const comicFrame &f) { m_frames.push_back(f); }
	const comicFrame& operator[](uint idx) { return m_frames[idx]; }
	uint count() const { return m_frames.size(); }
	uint pageNumber() const { return m_page; }
};


#endif /* COMICFRAMES_H_ */
