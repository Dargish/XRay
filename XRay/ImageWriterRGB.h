#pragma once
#include "ImageWriter.h"

#include <iostream>


class ImageWriterRGB : public ImageWriter
{
public:
	struct BMPFileHeader
	{
		unsigned char header[2] = { 'B', 'M' };
		int32_t filesize;
		int32_t reserved = 0;
		int32_t offset = 26;
	};

	struct BMPV5Header
	{
		int32_t headerSize = 12;
		uint16_t imageWidth;
		uint16_t imageHeight;
		uint16_t numPlanes = 1;
		uint16_t bitsPerPixel = 4;
	};

	ImageWriterRGB();

	virtual void writeImage(const Image& image, const std::string& path) const override;
};

