#pragma once

#undef RGB

struct RGB
{
	float r, g, b;

	RGB();
	RGB(float v);
	RGB(float r, float g, float b);

	RGB& operator+=(const RGB& other);
	RGB operator+(const RGB& other) const;
	RGB& operator-=(const RGB& other);
	RGB operator-(const RGB& other) const;
	RGB& operator*=(const RGB& other);
	RGB operator*(const RGB& other) const;
	RGB& operator/=(const RGB& other);
	RGB operator/(const RGB& other) const;
	RGB& operator*=(float value);
	RGB operator*(float value) const;
	RGB& operator/=(float value);
	RGB operator/(float value) const;

	RGB pow(float power) const;

	RGB& saturate();
	RGB saturated() const;
};