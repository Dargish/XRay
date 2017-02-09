#pragma once

#include "fwd.h"

class Intersectable
{
public:
	virtual ~Intersectable();

	const ShaderPtr& shader() const;
	void setShader(const ShaderPtr& shader);

	virtual bool intersect(const Ray& ray, float& t, Vector3& normal) const = 0;

private:
	ShaderPtr m_shader;
};

