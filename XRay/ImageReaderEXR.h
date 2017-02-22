#pragma once

#include "ImageReader.h"

#include <iosfwd>


class ImageReaderEXR : public ImageReader
{
public:
	ImageReaderEXR();

	virtual void readImage(Image& image, const std::wstring& path) const override;
};

