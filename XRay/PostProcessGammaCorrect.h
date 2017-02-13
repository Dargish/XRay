#pragma once

#include "PostProcess.h"


class PostProcessGammaCorrect : public PostProcess
{
public:
	virtual void process(Image& image) const override;
};
