#pragma once

#include "PostProcess.h"


class PostProcessToneMap : public PostProcess
{
public:
	virtual void process(Image& image) const override;
};

typedef std::shared_ptr<PostProcessToneMap> PostProcessToneMapPtr;

