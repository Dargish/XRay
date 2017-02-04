#pragma once

#include "Intersectable.h"

#include <vector>
#include <memory>
#include <limits>

typedef std::shared_ptr<Intersectable> IntersectablePtr;
typedef std::vector<IntersectablePtr> IntersectablePtrs;


class Scene
{
public:
	struct RayIntersectionResult
	{
		float distance;
		IntersectablePtr intersectable;

		RayIntersectionResult(float maxDistance = std::numeric_limits<float>::max());
	};

	Scene();

	template <typename INTERSECTABLE_TYPE, typename ...Args>
	std::shared_ptr<INTERSECTABLE_TYPE>& addIntersectable(Args... args);

	bool shootRay(const Ray& ray, RayIntersectionResult& result) const;

private:
	IntersectablePtrs m_intersectables;
};

template <typename INTERSECTABLE_TYPE, typename ...Args>
std::shared_ptr<INTERSECTABLE_TYPE>& Scene::addIntersectable(Args... args)
{
	m_intersectables.push_back(std::make_shared<INTERSECTABLE_TYPE>(args...));
	return std::dynamic_pointer_cast<INTERSECTABLE_TYPE>(m_intersectables.back());
}

