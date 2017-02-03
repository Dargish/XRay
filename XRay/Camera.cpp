#include "Camera.h"


Camera::Camera(
	const Vector3& position_ /*= Vector3(0.0f, 0.0f, 0.0f)*/,
	const Vector3& direction_ /*= Vector3(0.0f, 0.0f, 1.0f)*/,
	const Vector3& up_ /*= Vector3(0.0f, 1.0f, 0.0f)*/,
	float focalLength_ /*= 0.028f*/,
	float fStop_ /*= 2.0f*/
) :
	m_position(position_),
	m_direction(direction_),
	m_up(up_),
	m_focalLength(focalLength_),
	m_fStop(fStop_)
{
	m_direction.normalize();
	m_up.normalize();
	m_right = m_direction.cross(m_up);
	m_right.normalize();
	m_aperture = m_focalLength / m_fStop;
}

const Vector3& Camera::position() const
{
	return m_position;
}

const Vector3& Camera::direction() const
{
	return m_direction;
}

const Vector3& Camera::up() const
{
	return m_up;
}

float Camera::focalLength() const
{
	return m_focalLength;
}

float Camera::fStop() const
{
	return m_fStop;
}

void Camera::setPosition(const Vector3& position_)
{
	m_position = position_;
}

void Camera::setDirection(const Vector3& direction_)
{
	m_direction = direction_;
	m_direction.normalize();
	m_right = m_direction.cross(m_up);
	m_right.normalize();
}

void Camera::setUp(const Vector3& up_)
{
	m_up = up_;
	m_up.normalize();
	m_right = m_direction.cross(m_up);
	m_right.normalize();
}

void Camera::setFocalLength(float focalLength_)
{
	m_focalLength = focalLength_;
	m_aperture = m_focalLength / m_fStop;
}

void Camera::setFStop(float fStop_)
{
	m_fStop = fStop_;
	m_aperture = m_focalLength / m_fStop;
}

Ray Camera::ray(float x, float y)
{
	Vector3 screenPoint = m_position + m_direction * m_focalLength;
	screenPoint += m_right * m_aperture * x;
	screenPoint += m_up * m_aperture * y;
	return Ray(m_position, (screenPoint - m_position).normalize());
}
