#pragma once

#include "fwd.h"

#include <string>


class ImageWriter
{
public:
	ImageWriter() { };

	virtual ~ImageWriter() { };

	virtual void writeImage(const Image& image, const std::wstring& path) const = 0;
};

