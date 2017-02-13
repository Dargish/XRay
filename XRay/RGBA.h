#pragma once

#include "fwd.h"


struct RGBA
{
	float r, g, b, a;

	RGBA();
	RGBA(float v);
	RGBA(float r, float g, float b, float a = 1.0f);

	RGBA(const RGB& rgb, float a = 1.0f);

	RGBA& operator=(const RGB& rgb);

	RGBA& operator+=(const RGBA& other);
	RGBA operator+(const RGBA& other) const;
	RGBA& operator-=(const RGBA& other);
	RGBA operator-(const RGBA& other) const;
	RGBA& operator*=(const RGBA& other);
	RGBA operator*(const RGBA& other) const;
	RGBA& operator/=(const RGBA& other);
	RGBA operator/(const RGBA& other) const;
	RGBA& operator*=(const RGB& value);
	RGBA operator*(const RGB& value) const;
	RGBA& operator/=(const RGB& value);
	RGBA operator/(const RGB& value) const;
	RGBA& operator*=(float value);
	RGBA operator*(float value) const;
	RGBA& operator/=(float value);
	RGBA operator/(float value) const;

	RGBA& saturate();
	RGBA saturated() const;
};