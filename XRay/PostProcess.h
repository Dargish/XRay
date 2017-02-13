#pragma once

#include "fwd.h"


class PostProcess
{
public:
	PostProcess() { }

	virtual ~PostProcess() { }

	virtual void process(Image& image) const = 0;
};



class PostProcessStack
{
public:
	template <typename POSTPROCESS_TYPE>
	std::shared_ptr<POSTPROCESS_TYPE> push();

	void process(Image& image) const;

private:
	PostProcessPtrs m_stack;
};

template <typename POSTPROCESS_TYPE>
std::shared_ptr<POSTPROCESS_TYPE> PostProcessStack::push()
{
	m_stack.emplace_back(std::make_shared<POSTPROCESS_TYPE>());
	return std::dynamic_pointer_cast<POSTPROCESS_TYPE>(m_stack.back());
}

