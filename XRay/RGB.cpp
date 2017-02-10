#include "RGB.h"

#include <algorithm>


RGB::RGB(float r_ /*= 0.0f*/, float g_ /*= 0.0f*/, float b_ /*= 0.0f*/) :
	r(r_), g(g_), b(b_)
{

}

RGB& RGB::operator+=(const RGB& other)
{
	r += other.r;
	g += other.g;
	b += other.b;
	return *this;
}

RGB RGB::operator+(const RGB& other) const
{
	return RGB(r + other.r, g + other.g, b + other.b);
}

RGB& RGB::operator-=(const RGB& other)
{
	r -= other.r;
	g -= other.g;
	b -= other.b;
	return *this;
}

RGB RGB::operator-(const RGB& other) const
{
	return RGB(r - other.r, g - other.g, b - other.b);
}

RGB& RGB::operator*=(float value)
{
	r *= value;
	g *= value;
	b *= value;
	return *this;
}

RGB RGB::operator*(float value) const
{
	return RGB(r * value, g * value, b * value);
}

RGB& RGB::operator/=(float value)
{
	r /= value;
	g /= value;
	b /= value;
	return *this;
}

RGB RGB::operator/(float value) const
{
	return RGB(r / value, g / value, b / value);
}

RGB& RGB::saturate()
{
	r = std::max(0.0f, r);
	g = std::max(0.0f, g);
	b = std::max(0.0f, b);
	return *this;
}

RGB RGB::saturated() const
{
	return RGB(
		std::max(0.0f, r),
		std::max(0.0f, g),
		std::max(0.0f, b)
	);
}