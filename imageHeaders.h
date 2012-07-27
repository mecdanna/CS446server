#ifndef ABSTRACT_IMAGE_HEADER_H
#define ABSTRACT_IMAGE_HEADER_H

#include <istream>
#include <cstdint>    // uint32_t
#include <cassert>    // assert
#include <cstring>    // memcpy

typedef unsigned char byte;
typedef void* rawPicInMem;

// Abstact Image Header class for processing 
class AbstractImageHeader {

  public:
	enum Endianness { LITTLEENDIAN , BIGENDIAN };
	virtual byte* getHeader() = 0;
	virtual unsigned int getHeaderSize() = 0;
	virtual Endianness getEndianness() = 0;

	virtual unsigned int getImageWidth() = 0;
	virtual unsigned int getImageHeight() = 0;

	virtual std::uint32_t getField(unsigned int byteStartIndex, unsigned int numBytes) {
#ifdef _DEBUG
		assert((byteIndexIndex + numBytes) < getHeaderSize());
		assert(numBytes <= 4);
#endif

		byte * header = getHeader();
        std::uint32_t accumulator = 0;
		unsigned int byteOrder[4] = {0, 1, 2, 3};  // default to little endian
		unsigned byteEndIndex = byteStartIndex + numBytes;

        if ( getEndianness() == LITTLEENDIAN ) {
            //default
        } else if ( getEndianness() == BIGENDIAN ) {
            for( int i = 0; i < numBytes; i += 1 ) {
                byteOrder[i] = numBytes - i - 1;
            }
		} else {
			assert(false);
		}

		for( int i = 0; i < numBytes; i += 1) {
			accumulator |= header[byteStartIndex + i] << 8*byteOrder[i];
		}

		return accumulator;
	}

	// Read from file
	virtual void readHeader(std::istream & in) {
		unsigned int pos = in.tellg();
		in.read((char *)(getHeader()), getHeaderSize());
		in.seekg(pos, std::ios::beg);
	}

	// Read from memory
	virtual void readHeader(rawPicInMem in) {
		memcpy ( getHeader(), in, getHeaderSize() );
	}

};

class BmpHeader : public AbstractImageHeader {

  private:
	byte m_header[54];

  public:
	unsigned int getImageWidth() { return getField(18,4); }
	unsigned int getImageHeight() { return getField(22,4); }
	byte* getHeader() { return m_header; }
	unsigned int getHeaderSize() { return sizeof(m_header); }
	Endianness getEndianness() { return LITTLEENDIAN; }
};

class PngHeader : public AbstractImageHeader {

  private:
	byte m_header[24];

  public:
	unsigned int getImageWidth() { return getField(16,4); }
	unsigned int getImageHeight() { return getField(20,4); }
	byte* getHeader() { return m_header; }
	unsigned int getHeaderSize() { return sizeof(m_header); }
	Endianness getEndianness() { return BIGENDIAN; }
};

#endif
