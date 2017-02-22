#pragma once

#include "fwd.h"

#include <string>


class ImageReader
{
public:
	ImageReader() { };

	virtual ~ImageReader() { };

	virtual void readImage(Image& image, const std::wstring& path) const = 0;
};

