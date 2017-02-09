#include "Scene.h"
#include "Ray.h"
#include "Intersectable.h"


Scene::Scene()
{

}

bool Scene::shootRay(Ray& ray, RayIntersectionResult& result) const
{
	for (const IntersectablePtr& intersectable : m_intersectables)
	{
		float t;
		Vector3 normal;
		if (intersectable->intersect(ray, t, normal))
		{
			if (t < ray.distance)
			{
				ray.distance = t;
				result.intersectable = intersectable;
				result.normal = normal;
			}
		}
	}
	return bool(result.intersectable);
}
