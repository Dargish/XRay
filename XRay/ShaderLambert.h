#pragma once

#include "Shader.h"
#include "RGB.h"

class ShaderLambert : public Shader
{
public:
	ShaderLambert();
	ShaderLambert(const RGB& diffuse, float roughness, const RGB& indexOfRefraction);

	const RGB& diffuse() const;
	void setDiffuse(const RGB& diffuse);

	float roughness() const;
	void setRoughness(float roughness);

	const RGB& indexOfRefraction() const;
	void setIndexOfRefraction(const RGB& indexOfRefraction);

	RGBA shade(const RayTracer& rayTracer, const Ray& ray, const Vector3& normal, const LightPtrs& lights) const override;

private:
	float diffuseOrenNayer(float VoL, float NoL, float NoV) const;
	RGB schlickFresnel(float LoH) const;
	float geometricNeumann(float NoL, float NoV) const;
	float dGGX(float NoH) const;

	RGB m_diffuse;
	float m_roughness;
	RGB m_indexOfRefraction;
	RGB m_f0;
};

