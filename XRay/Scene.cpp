#include "Scene.h"
#include "Ray.h"
#include "Intersectable.h"


Scene::Scene()
{

}

const IntersectablePtrs& Scene::intersectables() const
{
	return m_intersectables;
}

const LightPtrs& Scene::lights() const
{
	return m_lights;
}

bool Scene::shootRay(Ray& ray, RayIntersectionResult* result /*= NULL*/) const
{
	bool hit = false;
	for (const IntersectablePtr& intersectable : m_intersectables)
	{
		float t;
		Vector3 normal;
		if (intersectable->intersect(ray, t, normal))
		{
			hit = true;
			if (t < ray.distance)
			{
				ray.distance = t;
				if (result)
				{
					result->intersectable = intersectable;
					result->normal = normal;
				}
			}
		}
	}
	return hit;
}
