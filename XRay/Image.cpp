#include "Image.h"


Image::Image(size_t width /*= 0*/, size_t height /*= 0*/) :
	m_width(width), m_height(height), m_pixels(m_width * m_height)
{
	
}

RGBA& Image::pixel(size_t w, size_t h)
{
	return m_pixels[h * m_width + w];
}

const RGBA& Image::pixel(size_t w, size_t h) const
{
	return m_pixels[h * m_width + w];
}

RGBA Image::sample(float x, float y) const
{
	float sx = x * m_width;
	float sy = y * m_height;
	size_t x0 = (size_t)std::floorf(sx);
	size_t y0 = (size_t)std::floorf(sy);
	size_t x1 = (x0 + 1) % m_width;
	size_t y1 = (y0 + 1) % m_height;
	float lx = sx - x0;
	float nlx = 1.0f - lx;
	float ly = sy - y0;
	float nly = 1.0f - ly;
	const RGBA& s00 = pixel(x0, y0);
	const RGBA& s01 = pixel(x0, y1);
	const RGBA& s10 = pixel(x1, y0);
	const RGBA& s11 = pixel(x1, y1);
	RGBA s0 = s00 * nlx + s10 * lx;
	RGBA s1 = s01 * nlx + s11 * lx;
	return s0 * nly + s1 * ly;
}

size_t Image::width() const
{
	return m_width;
}

size_t Image::height() const
{
	return m_height;
}

void Image::resize(size_t width, size_t height)
{
	m_width = width;
	m_height = height;
	m_pixels.resize(m_width * m_height);
}

float Image::aspectRatio() const
{
	return float(m_width) / float(m_height);
}

float Image::x(size_t w) const
{
	return (((float(w) + 0.5f) / float(m_width)) * 2.0f) - 1.0f;
}

float Image::y(size_t h) const
{
	return (((float(h) + 0.5f) / float(m_height)) * 2.0f) - 1.0f;
}

ImageLock::ImageLock(Image& image) : m_image(image)
{
	m_image.m_mutex.lock();
}

ImageLock::~ImageLock()
{
	m_image.m_mutex.unlock();
}