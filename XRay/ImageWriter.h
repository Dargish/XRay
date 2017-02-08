#pragma once

#include "Image.h"

#include <string>


typedef unsigned char ubyte;

class ImageWriter
{
public:
	ImageWriter() { };

	virtual ~ImageWriter() { };

	virtual void writeImage(const Image& image, const std::string& path) const = 0;
};

