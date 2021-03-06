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

/* 
 * Very important: STORE IN BGR NOT RGB FORMAT.
 * pixel = 8.8.8.8 => blue.green.red.nothing (last byte is ignored)
 */

//If you don't believe it works, go to photoshop and check
inline byte grayscale(pixel p) {
	byte red =   (p & 0x0000FF00) >> 8;
	byte green = (p & 0x00FF0000) >> 16;
	byte blue =  (p & 0xFF000000) >> 24;
	
	return red * .30 + green * .59 + .11 * blue;
}

/*
 * This is a generic image which we convert other images into. The alternative was to
 * make each image type derive from this, but there's a lot of encoding types, and it 
 * gets really messy that way.
 */
template <typename T>
class AbstractImage {
protected:
	T* data; //the actual image bitmap
	short* inUse; //how many AIs are using the same data, to allow shallow copying
	unsigned int m_width;
	unsigned int m_height;
public:
	AbstractImage(unsigned int w, unsigned int h) : m_width(w), m_height(h) {
		data = new T[w*h];
		inUse = new short(1);
	}
	
	AbstractImage() { inUse = nullptr; }

	virtual ~AbstractImage() {
        if (!inUse) {
			if(data) { //this could be an assertion, but it's easier to be safe
				delete [] data;
			}
			return;
		}
        --(*inUse);

		if(!*inUse) {
            delete [] data;
            delete inUse;
        }
	}
	
	AbstractImage(const AbstractImage& AI) {
		data = AI.data;
        inUse = AI.inUse;
		m_width = AI.m_width;
		m_height = AI.m_height;
		if (inUse) {
			++(*inUse);
		}
	}
 
    AbstractImage& operator=(const AbstractImage& AI) {
		data = AI.data;
        inUse = AI.inUse;
		m_width = AI.m_width;
		m_height = AI.m_height;
		if (inUse) {
			++(*inUse);
		}
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
	
	/*
	 * Binarizes an image by converting it to 2 colours based on a 
	 * threshold applied to a greyscale version of the image
	 */
	AbstractImage<byte> binarize(byte thmin) {
		AbstractImage<byte> bimg(m_width, m_height);
		
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
