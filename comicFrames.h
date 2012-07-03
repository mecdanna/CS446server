/*
 * comicFrames.h
 *
 *  Created on: 2012-07-02
 *      Author: mike
 */

#ifndef COMICFRAMES_H_
#define COMICFRAMES_H_

#include <vector>

struct comicFrame {
	comicFrame() {}

	comicFrame(int x, int y, int w, int h, int label) : x(x), y(y), w(w), h(h), lbl(label) {}

	int width() {return w;}
	int height() {return h;}
	int xPos() {return x;}
	int yPos() {return y;}
	int label() {return lbl;}

private:
	int x, y, w, h, lbl;
};

class ComicFrames {
	int m_page;
	int m_pageWidth;
	int m_pageHeight;
	std::vector<comicFrame> m_frames;
public:
	ComicFrames(int page = -1, int width = 0, int height = 0);
	~ComicFrames();

	void append(const comicFrame &f);
	const comicFrame& operator[](int idx);
	int count() const {return m_frames.size();}
	int pageNumber() const {return m_page;}
};


#endif /* COMICFRAMES_H_ */
