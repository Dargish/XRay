#include "RGBA.h"
#include "RGB.h"

#include <algorithm>


RGBA::RGBA(float r_ /*= 0.0f*/, float g_ /*= 0.0f*/, float b_ /*= 0.0f*/, float a_ /*= 1.0f*/) :
	r(r_), g(g_), b(b_), a(a_)
{

}

RGBA::RGBA(const RGB& rgb, float a_ /*= 0.0f*/) :
	r(rgb.r), g(rgb.g), b(rgb.b), a(a_)
{

}

RGBA& RGBA::operator=(const RGB& rgb)
{
	r = rgb.r;
	g = rgb.g;
	b = rgb.b;
	a = 1.0f;
	return *this;
}

RGBA& RGBA::operator+=(const RGBA& other)
{
	r += other.r;
	g += other.g;
	b += other.b;
	a += other.a;
	return *this;
}

RGBA RGBA::operator+(const RGBA& other) const
{
	return RGBA(r + other.r, g + other.g, b + other.b, a + other.a);
}

RGBA& RGBA::operator-=(const RGBA& other)
{
	r -= other.r;
	g -= other.g;
	b -= other.b;
	a -= other.a;
	return *this;
}

RGBA RGBA::operator-(const RGBA& other) const
{
	return RGBA(r - other.r, g - other.g, b - other.b, a - other.a);
}

RGBA& RGBA::operator*=(const RGBA& other)
{
	r *= other.r;
	g *= other.g;
	b *= other.b;
	a *= other.a;
	return *this;
}

RGBA RGBA::operator*(const RGBA& other) const
{
	return RGBA(r * other.r, g * other.g, b * other.b, a * other.a);
}

RGBA& RGBA::operator/=(const RGBA& other)
{
	r /= other.r;
	g /= other.g;
	b /= other.b;
	a /= other.a;
	return *this;
}

RGBA RGBA::operator/(const RGBA& other) const
{
	return RGBA(r / other.r, g / other.g, b / other.b, a / other.a);
}

RGBA& RGBA::operator*=(const RGB& value)
{
	r *= value.r;
	g *= value.g;
	b *= value.b;
	return *this;
}

RGBA RGBA::operator*(const RGB& value) const
{
	return RGBA(r * value.r, g * value.g, b * value.b, a);
}

RGBA& RGBA::operator/=(const RGB& value)
{
	r /= value.r;
	g /= value.g;
	b /= value.b;
	return *this;
}

RGBA RGBA::operator/(const RGB& value) const
{
	return RGBA(r / value.r, g / value.g, b / value.b, a);
}

RGBA& RGBA::operator*=(float value)
{
	r *= value;
	g *= value;
	b *= value;
	a *= value;
	return *this;
}

RGBA RGBA::operator*(float value) const
{
	return RGBA(r * value, g * value, b * value, a * value);
}

RGBA& RGBA::operator/=(float value)
{
	r /= value;
	g /= value;
	b /= value;
	a /= value;
	return *this;
}

RGBA RGBA::operator/(float value) const
{
	return RGBA(r / value, g / value, b / value, a / value);
}

RGBA& RGBA::saturate()
{
	r = std::max(0.0f, r);
	g = std::max(0.0f, g);
	b = std::max(0.0f, b);
	a = std::max(0.0f, a);
	return *this;
}

RGBA RGBA::saturated() const
{
	return RGBA(
		std::max(0.0f, r),
		std::max(0.0f, g),
		std::max(0.0f, b),
		std::max(0.0f, a)
	);
}