#include "Image.h"


Image::Image(size_t width /*= 0*/, size_t height /*= 0*/) :
	m_width(width), m_height(height), m_pixels(m_width * m_height)
{
	
}

Image::Pixel& Image::pixel(size_t x, size_t y)
{
	return m_pixels[y * m_width + x];
}

const Image::Pixel& Image::pixel(size_t x, size_t y) const
{
	return m_pixels[y * m_width + x];
}
