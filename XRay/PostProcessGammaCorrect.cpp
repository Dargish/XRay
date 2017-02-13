#include "PostProcessGammaCorrect.h"
#include "Image.h"


void PostProcessGammaCorrect::process(Image& image) const
{
	float power = 1.0f / 2.2f;
	for (size_t h = 0; h < image.height(); ++h)
	{
		for (size_t w = 0; w < image.width(); ++w)
		{
			RGBA& p = image.pixel(w, h);
			p.r = std::powf(p.r, power);
			p.g = std::powf(p.g, power);
			p.b = std::powf(p.b, power);
		}
	}
}
