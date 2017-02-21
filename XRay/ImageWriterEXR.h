#pragma once

#pragma once
#include "ImageWriter.h"

#include <iosfwd>


class ImageWriterEXR : public ImageWriter
{
public:
	ImageWriterEXR();

	virtual void writeImage(const Image& image, const std::string& path) const override;
};

