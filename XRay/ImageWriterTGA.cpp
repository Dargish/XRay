#include "ImageWriterTGA.h"
#include "Image.h"
#include "Math.h"

#include <fstream>


void ImageWriterTGA::Header::write(std::ofstream& f)
{
	f.put((char)idLength);              //0
	f.put((char)colorMapType);          //1
	f.put((char)imageType);             //2
	f.put((char)colorMapIndex);         //3
	f.put((char)(colorMapIndex >> 8));  //4
	f.put((char)colorMapLength);        //5
	f.put((char)(colorMapLength >> 8)); //6
	f.put((char)colorMapEntrySize);     //7
	f.put((char)xOrigin);               //8
	f.put((char)(xOrigin >> 8));        //9
	f.put((char)yOrigin);               //10
	f.put((char)(yOrigin >> 8));        //11
	f.put((char)imageWidth);            //12
	f.put((char)(imageWidth >> 8));     //13
	f.put((char)imageHeight);           //14
	f.put((char)(imageHeight >> 8));    //15
	f.put((char)pixelDepth);            //16
	f.put((char)imageDescriptor);       //17
}

ImageWriterTGA::ImageWriterTGA()
{

}

void ImageWriterTGA::writeImage(const Image& image, const std::string& path) const
{
	Header header;
	header.imageWidth = (short)image.width();
	header.imageHeight = (short)image.height();
	header.pixelDepth = 32;

	std::ofstream f(path, std::ios_base::out | std::ios_base::binary);
	f.imbue(std::locale::classic());

	header.write(f);

	for (size_t h = image.height(); h > 0; --h)
	{
		for (size_t w = 0; w < image.width(); ++w)
		{
			const RGBA& p = image.pixel(w, h - 1);
			uint8_t pd[] = { (uint8_t)(saturate(p.b) * 255), (uint8_t)(saturate(p.g) * 255), (uint8_t)(saturate(p.r) * 255), (uint8_t)(saturate(p.a) * 255) };
			f.write((const char*)pd, 4);
		}
	}
}