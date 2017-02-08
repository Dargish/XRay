#pragma once

#include "Ray.h"


class Camera
{
public:
	Camera(
		const Vector3& position = Vector3(0.0f, 0.0f, 0.0f),
		const Vector3& direction = Vector3(0.0f, 0.0f, 1.0f),
		const Vector3& up = Vector3(0.0f, 1.0f, 0.0f),
		float focalLength = 0.028f,
		float fStop = 2.0f,
		float aspectRatio = 1.0f
	);

	const Vector3& position() const;

	const Vector3& direction() const;

	const Vector3& up() const;

	float focalLength() const;

	float fStop() const;

	float aspectRatio() const;

	void setPosition(const Vector3& position);

	void setDirection(const Vector3& direction);

	void setUp(const Vector3& up);

	void setFocalLength(float focalLength);

	void setFStop(float fStop);

	void setAspectRatio(float aspectRatio);

	// x and y are in screen space -1.0 -> 1.0
	Ray ray(float x, float y) const;

private:
	Vector3 m_position;
	Vector3 m_direction;
	Vector3 m_up;
	Vector3 m_right;
	float m_focalLength;
	float m_fStop;
	float m_aperture;
	float m_aspectRatio;
};

