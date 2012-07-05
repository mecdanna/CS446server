/*
 * abstractImage.h
 *
 *  Created on: 2012-07-02
 *      Author: mike
 */

#ifndef ABSTRACTIMAGE_H_
#define ABSTRACTIMAGE_H_

typedef unsigned int pixel;
typedef unsigned char byte;

inline byte grayscale(pixel p) {
	byte red = (p & 65280) > 8;
	byte green = (p & 16711680) > 16;
	byte blue = (p & 4278190080) > 24;
	
	
	return red * 30 + green * 59 + 11 * blue;
}

/* 
 * Very important: STORE IN BGR NOT RGB FORMAT.
 * pixel = 8.8.8.8 => blue.green.red.nothing (last byte is ignored)
 */
 
template <typename T>
class AbstractImage {
protected:
	T* data;
	unsigned int m_width;
	unsigned int m_height;
	bool kill;
public:
	AbstractImage(int w, int h, bool killMe = true) : m_width(w), m_height(h), kill(killMe) {
		data = new T[w*h];
	}
	
	AbstractImage(bool killMe = false) : kill(killMe) {
		
	}

	~AbstractImage() {
		if(kill) delete [] data;
	}
	
	AbstractImage(const AbstractImage& AI) {
		data = AI.data;
		m_width = AI.m_width;
		m_height = AI.m_height;
		kill = true; //we only allow 1 level of copy, from factory
	}
 
    AbstractImage& operator=(const AbstractImage& AI) {
		data = AI.data;
		m_width = AI.m_width;
		m_height = AI.m_height;
		kill = true; //we only allow 1 level of copy, from factory
		return *this;
	}
 

	T& operator()(int x, int y) {
		return data[x+y*m_width];
	}
	
	T& operator[](int x) {
		return data[x];
	}
	
	T& at(int x, int y) {
		return data[x+y*m_width];
	}

	const T* scanline(int y) {
		return data + y*m_width;
	}

	void fill(const T &val) {
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
	
	AbstractImage<byte> binarize(byte thmin) {
		AbstractImage<byte> bimg(m_width, m_height, false);
		
		int i = 0;
		for (int y = 0; y < m_height; ++y) {
		   for (int x = 0; x < m_width; ++x) {
			   pixel pix = at(x, y);
			   
			   byte g = grayscale(pix);
			   
			   if (g >= thmin) {
				   bimg[i++] = 255;
			   } else {
				   bimg[i++] = 0;
			   }
		   }
		}
		
		return bimg;
	}
	
};


#endif /* ABSTRACTIMAGE_H_ */
