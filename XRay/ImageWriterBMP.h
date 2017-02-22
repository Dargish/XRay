#pragma once
#include "ImageWriter.h"

#include <iosfwd>

typedef unsigned char ubyte;

class ImageWriterBMP : public ImageWriter
{
public:
	struct BMPFileHeader
	{
		ubyte header0 = 'B';
		ubyte header1 = 'M';
		uint32_t filesize;
		uint32_t reserved = 0;
		uint32_t offset = 26;

		void write(std::ofstream& f);
	};

	struct BMPCoreHeader
	{
		int32_t headerSize = 12;
		uint16_t imageWidth;
		uint16_t imageHeight;
		uint16_t numPlanes = 1;
		uint16_t bitsPerPixel = 32;

		void write(std::ofstream& f);
	};

	ImageWriterBMP();

	virtual void writeImage(const Image& image, const std::wstring& path) const override;
};

