#include "EnvironmentMap.h"
#include "ImageReaderEXR.h"

EnvironmentMap::EnvironmentMap(const std::wstring& filepath)
{
	ImageReaderEXR reader;
	reader.readImage(m_image, filepath);
}

EnvironmentMap::~EnvironmentMap()
{

}