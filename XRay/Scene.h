#pragma once

#include "fwd.h"
#include "Vector3.h"

#include <vector>
#include <limits>
#include <memory>


typedef std::vector<IntersectablePtr> IntersectablePtrs;


class Scene
{
public:
	struct RayIntersectionResult
	{
		IntersectablePtr intersectable;
		Vector3 normal;
	};

	Scene();

	template <typename INTERSECTABLE_TYPE, typename ...Args>
	std::shared_ptr<INTERSECTABLE_TYPE> addIntersectable(Args... args);

	bool shootRay(Ray& ray, RayIntersectionResult& result) const;

private:
	IntersectablePtrs m_intersectables;
};

template <typename INTERSECTABLE_TYPE, typename ...Args>
std::shared_ptr<INTERSECTABLE_TYPE> Scene::addIntersectable(Args... args)
{
	m_intersectables.push_back(std::make_shared<INTERSECTABLE_TYPE>(args...));
	return std::dynamic_pointer_cast<INTERSECTABLE_TYPE>(m_intersectables.back());
}

