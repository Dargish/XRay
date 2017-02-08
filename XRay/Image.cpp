#include "Image.h"


Image::Color::Color(float r_ /*= 0.0f*/, float g_ /*= 0.0f*/, float b_ /*= 0.0f*/, float a_ /*= 0.0f*/) :
	r(r_), g(g_), b(b_), a(a_)
{

}

Image::Color& Image::Color::operator+=(const Color& other)
{
	r += other.r;
	g += other.g;
	b += other.b;
	a += other.a;
	return *this;
}

Image::Color Image::Color::operator+(const Color& other) const
{
	return Color(r + other.r, g + other.g, b + other.b, a + other.a);
}

Image::Color& Image::Color::operator/=(float value)
{
	r /= value;
	g /= value;
	b /= value;
	a /= value;
	return *this;
}

Image::Color Image::Color::operator/(float value) const
{
	return Color(r / value, g / value, b / value, a / value);
}

Image::Image(size_t width /*= 0*/, size_t height /*= 0*/) :
	m_width(width), m_height(height), m_pixels(m_width * m_height)
{
	
}

Image::Color& Image::pixel(size_t w, size_t h)
{
	return m_pixels[h * m_width + w];
}

const Image::Color& Image::pixel(size_t w, size_t h) const
{
	return m_pixels[h * m_width + w];
}

size_t Image::width() const
{
	return m_width;
}

size_t Image::height() const
{
	return m_height;
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