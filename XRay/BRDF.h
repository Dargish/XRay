#pragma once

#include "RGB.h"
#include "Vector3.h"

#include <memory>

class BRDF
{
public:
	struct Geometry
	{
		float NoV;
		float NoL;
		float VoL;
		float LoH;
		float NoH;

		Geometry(
			const Vector3& N,
			const Vector3& V,
			const Vector3& L
		);
	};
};

class DiffuseBRDF : public BRDF
{
public:
	virtual float operator()(const Geometry& geometry, float roughness) const = 0;
};

class FresnelBRDF : public BRDF
{
public:
	virtual RGB operator()(const Geometry& geometry, const RGB& f0) const = 0;
};

class GeometricBRDF : public BRDF
{
public:
	virtual float operator()(const Geometry& geometry) const = 0;
};

class DistributionBRDF : public BRDF
{
public:
	virtual float operator()(const Geometry& geometry, float roughness) const = 0;
};

typedef std::shared_ptr<DiffuseBRDF> DiffuseBRDFPtr;
typedef std::shared_ptr<FresnelBRDF> FresnelBRDFPtr;
typedef std::shared_ptr<GeometricBRDF> GeometricBRDFPtr;
typedef std::shared_ptr<DistributionBRDF> DistributionBRDFPtr;

class BRDFSet
{
public:
	const DiffuseBRDFPtr& diffuseBRDF() const;
	const FresnelBRDFPtr& fresnelBRDF() const;
	const GeometricBRDFPtr& geometricBRDF() const;
	const DistributionBRDFPtr& distributionBRDF() const;

	template <typename DIFFUSE_BRDF>
	void setDiffuseBRDF();
	template <typename FRESNEL_BRDF>
	void setFresnelBRDF();
	template <typename GEOMETRIC_BRDF>
	void setGeometricBRDF();
	template <typename DISTRIBUTION_BRDF>
	void setDistributionBRDF();

	float diffuse(const BRDF::Geometry& geometry, float roughness) const;
	RGB specular(const BRDF::Geometry& geometry, float roughness, RGB f0) const;

protected:
	DiffuseBRDFPtr m_diffuseBRDF;
	FresnelBRDFPtr m_fresnelBRDF;
	GeometricBRDFPtr m_geometricBRDF;
	DistributionBRDFPtr m_distributionBRDF;
};

typedef std::shared_ptr<BRDFSet> BRDFSetPtr;

template <
	typename DIFFUSE_BRDF,
	typename FRESNEL_BRDF,
	typename GEOMETRIC_BRDF,
	typename DISTRIBUTION_BRDF
>
class TypedBRDFSet : public BRDFSet
{
public:
	TypedBRDFSet();
};

template <typename DIFFUSE_BRDF>
void BRDFSet::setDiffuseBRDF()
{
	m_diffuseBRDF.reset(new DIFFUSE_BRDF);
}

template <typename FRESNEL_BRDF>
void BRDFSet::setFresnelBRDF()
{
	m_fresnelBRDF.reset(new FRESNEL_BRDF);
}

template <typename GEOMETRIC_BRDF>
void BRDFSet::setGeometricBRDF()
{
	m_geometricBRDF.reset(new GEOMETRIC_BRDF);
}

template <typename DISTRIBUTION_BRDF>
void BRDFSet::setDistributionBRDF()
{
	m_distributionBRDF.reset(new DISTRIBUTION_BRDF);
}

template <
	typename DIFFUSE_BRDF,
	typename FRESNEL_BRDF,
	typename GEOMETRIC_BRDF,
	typename DISTRIBUTION_BRDF
>
TypedBRDFSet<DIFFUSE_BRDF, FRESNEL_BRDF, GEOMETRIC_BRDF, DISTRIBUTION_BRDF>::TypedBRDFSet()
{
	m_diffuseBRDF.reset(new DIFFUSE_BRDF);
	m_fresnelBRDF.reset(new FRESNEL_BRDF);
	m_geometricBRDF.reset(new GEOMETRIC_BRDF);
	m_distributionBRDF.reset(new DISTRIBUTION_BRDF);
}