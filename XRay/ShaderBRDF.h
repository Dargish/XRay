#pragma once

#include "Shader.h"
#include "RGB.h"
#include "BRDF.h"

class ShaderBRDF : public Shader
{
public:
	ShaderBRDF(const BRDFSetPtr& brdfSet);
	ShaderBRDF(const BRDFSetPtr& brdfSet, const RGB& diffuse, float roughness, const RGB& f0);

	const RGB& diffuse() const;
	void setDiffuse(const RGB& diffuse);

	float roughness() const;
	void setRoughness(float roughness);

	const RGB& f0() const;
	void setF0(const RGB& f0);

	RGBA shade(const RayTracer& rayTracer, const Ray& ray, const Vector3& normal, const LightPtrs& lights) const override;

private:
	RGB m_diffuse;
	float m_roughness;
	RGB m_indexOfRefraction;
	RGB m_f0;

	BRDFSetPtr m_brdfSet;
};

