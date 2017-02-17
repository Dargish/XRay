#include "BRDF.h"

BRDF::Geometry::Geometry(
	const Vector3& N,
	const Vector3& V,
	const Vector3& L
)
{
	NoV = N.dot(V);
	NoL = N.dot(L);
	VoL = V.dot(L);
	Vector3 H = (V + L).normalize();
	LoH = L.dot(H);
	NoH = N.dot(H);
}

const DiffuseBRDFPtr& BRDFSet::diffuseBRDF() const
{
	return m_diffuseBRDF;
}

const FresnelBRDFPtr& BRDFSet::fresnelBRDF() const
{
	return m_fresnelBRDF;
}

const GeometricBRDFPtr& BRDFSet::geometricBRDF() const
{
	return m_geometricBRDF;
}

const DistributionBRDFPtr& BRDFSet::distributionBRDF() const
{
	return m_distributionBRDF;
}

float BRDFSet::diffuse(const BRDF::Geometry& geometry, float roughness) const
{
	float diffuse = 1.0f;
	if (m_diffuseBRDF)
	{
		diffuse = (*m_diffuseBRDF)(geometry, roughness);
	}
	return diffuse;
}

RGB BRDFSet::specular(const BRDF::Geometry& geometry, float roughness, RGB f0) const
{
	RGB fresnel(1.0f, 1.0f, 1.0f);
	if (m_fresnelBRDF)
	{
		fresnel = (*m_fresnelBRDF)(geometry, f0);
	}
	float geometric = 1.0f;
	if (m_geometricBRDF)
	{
		geometric = (*m_geometricBRDF)(geometry);
	}
	float distribution = 1.0f;
	if (m_distributionBRDF)
	{
		distribution = (*m_distributionBRDF)(geometry, roughness);
	}
	RGB specular = fresnel * geometric * distribution;
	specular /= 4.0f * geometry.NoL * geometry.NoV;
	return specular;
}
