#pragma once

#include "Shader.h"
#include "RGB.h"

class ShaderLambert : public Shader
{
public:
	ShaderLambert();
	ShaderLambert(RGB diffuse, float roughness);

	const RGB& diffuse() const;
	void setDiffuse(const RGB& diffuse);

	float roughness() const;
	void setRoughness(float roughness);

	RGBA shade(const RayTracer& rayTracer, const Ray& ray, const Vector3& normal) const override;

private:
	RGB m_diffuse;
	float m_roughness;
};

