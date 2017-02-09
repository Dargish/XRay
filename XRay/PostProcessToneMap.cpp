#include "PostProcessToneMap.h"
#include "Image.h"


void PostProcessToneMap::process(Image& image) const
{
	for (size_t h = 0; h < image.height(); ++h)
	{
		for (size_t w = 0; w < image.width(); ++w)
		{
			RGBA& p = image.pixel(w, h);
			p.r /= 10.0f;
			p.g /= 10.0f;
			p.b /= 10.0f;
		}
	}
}
