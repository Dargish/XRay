#include "PostProcess.h"


void PostProcessStack::process(Image& image) const
{
	for (const PostProcessPtr& postProcess : m_stack)
	{
		postProcess->process(image);
	}
}