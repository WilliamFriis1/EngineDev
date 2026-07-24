#pragma once

#include "Engine/Rendering/Graphics/Math/glm.h"
#include "transform.h"

class Camera
{
private:

	glm::mat4 viewMatrix;
	glm::mat4 projectionMatrix;

	Transform transform{};

	void updateView();
	void updateProj();

public:
	//Default values
	float fov = 45.0f;
	float aspect = 16.0f / 9.0f;
	float nearPlane = 0.1f;
	float farPlane = 100.0f;

	const glm::mat4& getViewMatrix() const;
	const glm::mat4& getProjectionMatrix() const;

	const Transform& getTransform() const;
	Transform& getTransform();

	void update();
};