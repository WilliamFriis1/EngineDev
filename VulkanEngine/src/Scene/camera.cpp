#include "camera.h"

void Camera::updateView()
{
	viewMatrix = glm::inverse(transform.getMatrix());
}

void Camera::updateProj()
{
	projectionMatrix = glm::perspective(glm::radians(fov), aspect, nearPlane, farPlane);

	//projectionMatrix[1][1] *= -1;
}

const glm::mat4& Camera::getViewMatrix() const
{
	return viewMatrix;
}

const glm::mat4& Camera::getProjectionMatrix() const
{
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

void Camera::update()
{
	updateProj();
	updateView();
}
