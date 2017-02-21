#pragma once
#include "ImageWriter.h"

#include <iosfwd>


class ImageWriterTGA : public ImageWriter
{
public:
	struct Header
	{
		ubyte idLength = 0;
		ubyte colorMapType = 0;
		ubyte imageType = 2;
		short colorMapIndex = 0;
		short colorMapLength = 0;
		ubyte colorMapEntrySize = 0;
		short xOrigin = 0;
		short yOrigin = 0;
		short imageWidth = 0;
		short imageHeight = 0;
		ubyte pixelDepth = 0;
		ubyte imageDescriptor = 0;

		void write(std::ofstream& f);
	};
	
	ImageWriterTGA();

	virtual void writeImage(const Image& image, const std::string& path) const override;
};

