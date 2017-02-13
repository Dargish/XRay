#pragma once

#include "fwd.h"
#include "Vector3.h"

#include <limits>


class Scene
{
public:
	struct RayIntersectionResult
	{
		IntersectablePtr intersectable;
		Vector3 normal;
	};

	Scene();

	const IntersectablePtrs& intersectables() const;
	const LightPtrs& lights() const;

	template <typename INTERSECTABLE_TYPE, typename ...Args>
	std::shared_ptr<INTERSECTABLE_TYPE> addIntersectable(Args... args);

	template <typename LIGHT_TYPE, typename ...Args>
	std::shared_ptr<LIGHT_TYPE> addLight(Args... args);

	bool shootRay(Ray& ray, RayIntersectionResult* result = NULL) const;

private:
	IntersectablePtrs m_intersectables;
	LightPtrs m_lights;
};

template <typename INTERSECTABLE_TYPE, typename ...Args>
std::shared_ptr<INTERSECTABLE_TYPE> Scene::addIntersectable(Args... args)
{
	m_intersectables.push_back(std::make_shared<INTERSECTABLE_TYPE>(args...));
	return std::dynamic_pointer_cast<INTERSECTABLE_TYPE>(m_intersectables.back());
}

template <typename LIGHT_TYPE, typename ...Args>
std::shared_ptr<LIGHT_TYPE> Scene::addLight(Args... args)
{
	m_lights.push_back(std::make_shared<LIGHT_TYPE>(args...));
	return std::dynamic_pointer_cast<LIGHT_TYPE>(m_lights.back());
}

