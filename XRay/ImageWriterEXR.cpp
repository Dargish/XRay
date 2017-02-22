#include "ImageWriterEXR.h"
#include "Image.h"
#include "Math.h"

#include <locale>
#include <codecvt>

#pragma warning( disable : 4996 4251 ) 

#define OPENEXR_DLL

#include <ImfRgbaFile.h>

using namespace OPENEXR_IMF_NAMESPACE;

ImageWriterEXR::ImageWriterEXR()
{

}

void ImageWriterEXR::writeImage(const Image& image, const std::wstring& pathUtf16) const
{
	std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> convert;
	std::string pathUtf8 = convert.to_bytes(pathUtf16);
	RgbaOutputFile fileOut(pathUtf8.c_str(), (int)image.width(), (int)image.height());

	std::vector<Rgba> frameBuffer(image.width() * image.height());

	for (size_t h = 0; h < image.height(); ++h)
	{
		for (size_t w = 0; w < image.width(); ++w)
		{
			Rgba& rgba = frameBuffer[w + h * image.width()];
			const RGBA& pixel = image.pixel(w, h);
			rgba.r = (half)pixel.r;
			rgba.g = (half)pixel.g;
			rgba.b = (half)pixel.b;
			rgba.a = (half)pixel.a;
		}
	}

	fileOut.setFrameBuffer(&frameBuffer.front(), 1, image.width());

	fileOut.writePixels((int)image.height());
}