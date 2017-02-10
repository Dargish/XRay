#pragma once

#undef RGB

struct RGB
{
	float r, g, b;

	RGB(float r = 0.0f, float g = 0.0f, float b = 0.0f);

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

	RGB& saturate();
	RGB saturated() const;
};