#include "Scene.h"


Scene::RayIntersectionResult::RayIntersectionResult(float maxDistance /*= std::numeric_limits<float>::max()*/) :
	distance(maxDistance)
{

}

Scene::Scene()
{

}

bool Scene::shootRay(const Ray& ray, RayIntersectionResult& result) const
{
	for (const IntersectablePtr& intersectable : m_intersectables)
	{
		float t;
		if (intersectable->intersect(ray, t))
		{
			if (t < result.distance)
			{
				result.distance = t;
				result.intersectable = intersectable;
			}
		}
	}
	return bool(result.intersectable);
}
