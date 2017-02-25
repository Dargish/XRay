#include "ImageReaderEXR.h"
#include "Image.h"
#include "Math.h"

#include <locale>
#include <codecvt>

#pragma warning( disable : 4996 4251 ) 

#define OPENEXR_DLL

#include <ImfRgbaFile.h>

using namespace OPENEXR_IMF_NAMESPACE;
using namespace IMATH_NAMESPACE;

ImageReaderEXR::ImageReaderEXR()
{

}

void ImageReaderEXR::readImage(Image& image, const std::wstring& pathUtf16) const
{
	std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> convert;
	std::string pathUtf8 = convert.to_bytes(pathUtf16);
	RgbaInputFile fileIn(pathUtf8.c_str());
	
	Box2i dw = fileIn.dataWindow();
	size_t width = dw.max.x - dw.min.x + 1;
	size_t height = dw.max.y - dw.min.y + 1;

	image.resize(width, height);

	std::vector<Rgba> frameBuffer(width * height);
	fileIn.setFrameBuffer(&frameBuffer.front(), 1, width);
	fileIn.readPixels(dw.min.y, dw.max.y);
}