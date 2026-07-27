#include "camera.h"

void Camera::updateView() const
{
	viewMatrix = glm::inverse(transform.getMatrix());

	dirtyView = false;
}

void Camera::updateProj() const
{
	projectionMatrix = glm::perspective(glm::radians(fov), aspect, nearPlane, farPlane);

	dirtyProj = false;
}

const glm::mat4& Camera::getViewMatrix() const
{
	if (dirtyView)
		updateView();

	return viewMatrix;
}

const glm::mat4& Camera::getProjectionMatrix() const
{
	if (dirtyProj)
		updateProj();

	return projectionMatrix;
}

const Transform& Camera::getTransform() const
{
	return transform;
}

Transform& Camera::getTransform()
{
	return transform;
}
