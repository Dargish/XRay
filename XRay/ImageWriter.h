#pragma once

#include "Image.h"

#include <string>


class ImageWriter
{
public:
	ImageWriter() { };

	virtual ~ImageWriter() { };

	virtual void writeImage(const Image& image, const std::string& path) const = 0;
};

