#include "ImageWriterBMP.h"
#include "Image.h"
#include "Math.h"

#include <fstream>


void ImageWriterBMP::BMPFileHeader::write(std::ofstream & f)
{
	f.put((char)header0);
	f.put((char)header1);
	f.put((char)filesize);
	f.put((char)(filesize >> 8));
	f.put((char)(filesize >> 16));
	f.put((char)(filesize >> 24));
	f.put((char)reserved);
	f.put((char)(reserved >> 8));
	f.put((char)(reserved >> 16));
	f.put((char)(reserved >> 24));
	f.put((char)offset);
	f.put((char)(offset >> 8));
	f.put((char)(offset >> 16));
	f.put((char)(offset >> 24));
}

void ImageWriterBMP::BMPCoreHeader::write(std::ofstream & f)
{
	f.put((char)headerSize);
	f.put((char)(headerSize >> 8));
	f.put((char)(headerSize >> 16));
	f.put((char)(headerSize >> 24));
	f.put((char)imageWidth);
	f.put((char)(imageWidth >> 8));
	f.put((char)imageHeight);
	f.put((char)(imageHeight >> 8));
	f.put((char)numPlanes);
	f.put((char)(numPlanes >> 8));
	f.put((char)bitsPerPixel);
	f.put((char)(bitsPerPixel >> 8));
}

ImageWriterBMP::ImageWriterBMP()
{

}

void ImageWriterBMP::writeImage(const Image& image, const std::string& path) const
{
	BMPFileHeader fileHeader;
	BMPCoreHeader v5Header;
	v5Header.imageWidth = (uint16_t)image.width();
	v5Header.imageHeight = (uint16_t)image.height();
	fileHeader.filesize = fileHeader.offset + v5Header.imageWidth * v5Header.imageHeight * v5Header.bitsPerPixel;

	std::ofstream f(path, std::ios_base::out | std::ios_base::binary);
	f.imbue(std::locale::classic());

	fileHeader.write(f);
	v5Header.write(f);

	for (size_t h = image.height(); h > 0; --h)
	{
		for (size_t w = 0; w < image.width(); ++w)
		{
			const RGBA& p = image.pixel(w, h - 1);
			uint8_t pd[] = { (uint8_t)(clamp(p.b) * 255), (uint8_t)(clamp(p.g) * 255), (uint8_t)(clamp(p.r) * 255), (uint8_t)(clamp(p.a) * 255) };
			f.write((const char*)pd, 4);
		}
	}
}
