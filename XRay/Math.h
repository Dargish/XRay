#pragma once

#include <cmath>
#include <algorithm>

#undef max
#undef min

#define HALF_PI_F 1.570796326795f
#define PI_F      3.141592653589f
#define PI_2F     6.283185307178f
#define EPS_F     0.000001f

inline bool fequals(float l, float r)
{
	return fabsf(l - r) < FLT_EPSILON;
}

inline float saturate(float v)
{
	return std::max(0.0f, v);
}

inline float clamp(float v, float min = 0.0f, float max = 1.0f)
{
	return std::max(min, std::min(max, v));
}
