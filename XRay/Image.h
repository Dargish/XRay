#pragma once

#include <vector>

#include <tbb/mutex.h>

class Image
{
public:
	struct Color
	{
		float r, g, b, a;

		Color(float r = 0.0f, float g = 0.0f, float b = 0.0f, float a = 0.0f);

		Color& operator+=(const Color& other);
		Color operator+(const Color& other) const;
		Color& operator/=(float value);
		Color operator/(float value) const;
	};

	typedef std::vector<Color> Pixels;

	Image(size_t width = 0, size_t height = 0);

	Color& pixel(size_t w, size_t h);
	const Color& pixel(size_t w, size_t h) const;

	size_t width() const;
	size_t height() const;

	float aspectRatio() const;

	float x(size_t w) const;
	float y(size_t h) const;

private:
	friend class ImageLock;

	size_t m_width, m_height;
	Pixels m_pixels;
	tbb::mutex m_mutex;
};

class ImageLock
{
public:
	ImageLock(Image& image);
	~ImageLock();

private:
	Image& m_image;
};

