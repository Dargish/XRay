#pragma once

#include <vector>

#include <tbb/mutex.h>

class Image
{
public:
	struct Pixel
	{
		float r, g, b, a;

		Pixel();
	};

	typedef std::vector<Pixel> Pixels;

	Image(size_t width = 0, size_t height = 0);

	Pixel& pixel(size_t w, size_t h);
	const Pixel& pixel(size_t w, size_t h) const;

	size_t width() const;
	size_t height() const;

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

