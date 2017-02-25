#pragma once

#include "RGBA.h"
#include "Image.h"
#include "Vector3.h"

class EnvironmentMap
{
public:
	EnvironmentMap(const std::wstring& filepath);

	virtual ~EnvironmentMap();

	virtual RGBA sample(const Vector3& direction) const = 0;

protected:
	Image m_image;
};