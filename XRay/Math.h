#pragma once

#include <cmath>
#include <algorithm>

#undef max
#undef min

#define PI_F 3.141592653589f
#define PI_2F 6.283185307178f

inline float saturate(float v)
{
	return std::max(0.0f, v);
}

inline float clamp(float v, float min = 0.0f, float max = 1.0f)
{
	return std::max(min, std::min(max, v));
}