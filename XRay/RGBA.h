#pragma once

#include "RGB.h"


struct RGBA
{
	float r, g, b, a;

	RGBA(float r = 0.0f, float g = 0.0f, float b = 0.0f, float a = 1.0f);

	RGBA(const RGB& rgb, float a = 1.0f);

	RGBA& operator=(const RGB& rgb);

	RGBA& operator+=(const RGBA& other);
	RGBA operator+(const RGBA& other) const;
	RGBA& operator-=(const RGBA& other);
	RGBA operator-(const RGBA& other) const;
	RGBA& operator*=(float value);
	RGBA operator*(float value) const;
	RGBA& operator/=(float value);
	RGBA operator/(float value) const;
};