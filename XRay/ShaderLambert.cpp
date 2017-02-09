#include "ShaderLambert.h"
#include "Scene.h"
#include "Math.h"
#include "Ray.h"
#include "Intersectable.h"

#include <algorithm>
#include <tbb/parallel_for.h>


ShaderLambert::ShaderLambert()
{

}

ShaderLambert::ShaderLambert(RGB diffuse_, float roughness_) :
	m_diffuse(diffuse_), m_roughness(roughness_)
{

}

const RGB& ShaderLambert::diffuse() const
{
	return m_diffuse;
}

void ShaderLambert::setDiffuse(const RGB& diffuse_)
{
	m_diffuse = diffuse_;
}

float ShaderLambert::roughness() const
{
	return m_roughness;
}

void ShaderLambert::setRoughness(float roughness_)
{
	m_roughness = roughness_;
}

RGBA ShaderLambert::shade(const Scene& scene, const Ray& ray, const Vector3& P, const Vector3& N) const
{
	float NoV = N.dot(ray.direction);
	Vector3 R = (ray.direction - N * NoV * 2.0f).normalize();

	RGBA reflection(0.0f, 0.0f, 0.0f, 0.0f);

	if (ray.childCount > 0)
	{
		Vector3 u, v;
		R.orthogonalVectors(u, v);

		float coneRadAngle = (1.0f - m_roughness) * PI_F;

		tbb::parallel_for(size_t(0), ray.childCount, [&](size_t r) {
			Vector3 randR = Vector3::RandomRay(R, u, v, coneRadAngle);
			Ray thisRay(P, randR);
			thisRay.childCount = ray.childCount / 2;
			Scene::RayIntersectionResult intersectionResult;
			if (scene.shootRay(thisRay, intersectionResult))
			{
				if (intersectionResult.intersectable->shader())
				{
					Vector3 P = thisRay.origin + thisRay.direction * thisRay.distance;
					reflection += intersectionResult.intersectable->shader()->shade(scene, thisRay, P, intersectionResult.normal);
				}
				else
				{
					reflection.a += 1.0;
				}
			}
		});
		reflection /= ray.childCount;
	}
	else
	{
		reflection = RGBA(0.5f, 0.5f, 0.5f, 0.5f);
	}

	
	return reflection + m_diffuse * (1.0f + NoV);
}
