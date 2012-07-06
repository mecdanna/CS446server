#include "comicFrames.h"

using namespace std;

ComicFrames::ComicFrames(uint page, uint width, uint height) : m_page(page), m_pageWidth(width), m_pageHeight(height) {
	
}

void ComicFrames::append(const comicFrame& f) {
	m_frames.push_back(f);
}

const comicFrame& ComicFrames::operator [](uint idx) {
	return m_frames[idx];
}

ComicFrames::~ComicFrames() {
	m_frames.clear();
}

