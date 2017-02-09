#include "Intersectable.h"


Intersectable::~Intersectable()
{

}

const ShaderPtr& Intersectable::shader() const
{
	return m_shader;
}

void Intersectable::setShader(const ShaderPtr& shader_)
{
	m_shader = shader_;
}