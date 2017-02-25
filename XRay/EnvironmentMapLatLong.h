#pragma once

#include "EnvironmentMap.h"

class EnvironmentMapLatLong : public EnvironmentMap
{
public:
	EnvironmentMapLatLong(const std::wstring& filepath);

	virtual RGBA sample(const Vector3& direction) const;
};