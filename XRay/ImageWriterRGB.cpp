#include "ImageWriterRGB.h"

#include <fstream>


ImageWriterRGB::ImageWriterRGB()
{

}

void ImageWriterRGB::writeImage(const Image& image, const std::string& path) const
{
	BMPFileHeader fileHeader;
	BMPV5Header v5Header;
	v5Header.imageWidth = (uint16_t)image.width();
	v5Header.imageHeight = (uint16_t)image.height();
	fileHeader.filesize = fileHeader.offset + v5Header.imageWidth * v5Header.imageHeight * v5Header.bitsPerPixel;

	std::cout << "Filesize: " << fileHeader.filesize << std::endl;

	std::ofstream f(path);

	f.write((const char*)&fileHeader.header[0], 1);
	f.write((const char*)&fileHeader.header[1], 1);
	f.write((const char*)&fileHeader.filesize, 4);
	f.write((const char*)&fileHeader.reserved, 4);
	f.write((const char*)&fileHeader.offset, 4);

	f.write((const char*)&v5Header.headerSize, 4);
	f.write((const char*)&v5Header.imageWidth, 2);
	f.write((const char*)&v5Header.imageHeight, 2);
	f.write((const char*)&v5Header.numPlanes, 2);
	f.write((const char*)&v5Header.bitsPerPixel, 2);

	std::cout << f.tellp() << std::endl;

	for (size_t h = 0; h < image.height(); ++h)
	{
		for (size_t w = 0; w < image.width(); ++w)
		{
			const Image::Pixel& p = image.pixel(w, h);
			uint8_t a = (uint8_t)(p.a * 255);
			uint8_t b = (uint8_t)(p.b * 255);
			uint8_t g = (uint8_t)(p.g * 255);
			uint8_t r = (uint8_t)(p.r * 255);
			std::cout << (uint32_t)a << ", " << (uint32_t)b << ", " << (uint32_t)g << ", " << (uint32_t)r << std::endl;
			f.write(reinterpret_cast<char*>(&a), 1);
			f.write(reinterpret_cast<char*>(&b), 1);
			f.write(reinterpret_cast<char*>(&g), 1);
			f.write(reinterpret_cast<char*>(&r), 1);
		}
	}

	std::cout << f.tellp() << std::endl;
}

std::ostream& operator<< (std::ostream& os, const ImageWriterRGB::BMPFileHeader& hdr)
{
	return os << hdr.header[0] << hdr.header[1] << hdr.filesize << hdr.reserved << hdr.offset;
}

std::ostream& operator<< (std::ostream& os, const ImageWriterRGB::BMPV5Header& hdr)
{
	return os << hdr.headerSize << hdr.imageWidth << hdr.imageHeight << hdr.numPlanes << hdr.bitsPerPixel;
}
