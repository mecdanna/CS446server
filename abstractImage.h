/*
 * abstractImage.h
 *
 *  Created on: 2012-07-02
 *      Author: mike
 */

#ifndef ABSTRACTIMAGE_H_
#define ABSTRACTIMAGE_H_

typedef unsigned int byte;

class AbstractImage {
protected:
	byte *data;
	unsigned int m_width;
	unsigned int m_height;

public:
	AbstractImage(int w, int h) : m_width(w), m_height(h) {
		data = new byte[w*h];
	}

	~AbstractImage() {
		delete [] data;
	}

	byte& operator()(int x, int y) {
		return data[x+y*m_width];
	}

	const byte* scanline(int y) {
		return data + y*m_width;
	}

	void fill(const byte &val) {
		for (int i=0; i< m_width * m_height; ++i) {
			data[i] = val;
		}
	}

	int width() const {
		return m_width;
	}

	int height() const {
		return m_height;
	}
};


#endif /* ABSTRACTIMAGE_H_ */
