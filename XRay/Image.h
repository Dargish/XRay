#pragma once

#include <vector>

class Image
{
public:
	struct Pixel
	{
		float r, g, b, a;
	};

	typedef std::vector<Pixel> Pixels;

	Image(size_t width = 0, size_t height = 0);

	Pixel& pixel(size_t x, size_t y);
	const Pixel& pixel(size_t x, size_t y) const;

private:
	size_t m_width, m_height;
	Pixels m_pixels;
};

