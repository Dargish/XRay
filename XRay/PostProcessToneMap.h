#pragma once

#include "PostProcess.h"


class PostProcessToneMap : public PostProcess
{
public:
	virtual void process(Image& image) const override;
};
