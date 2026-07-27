#pragma once

#include "Engine/Rendering/Graphics/Math/glm.h"

class Transform
{
private:
	glm::vec3 position{0.0f};
	glm::quat rotation = glm::identity<glm::quat>();
	glm::vec3 scaleValue{ 1.0f };

public:
	mutable glm::mat4 matrix{ 1.0f };
	mutable bool dirty = true;

	const glm::mat4& getMatrix() const;

	void setPosition(glm::vec3 newPosition);
	void translate(glm::vec3 newPosition);
	void rotate(glm::quat newRotation);
	void scale(glm::vec3 newRotation);

	void rebuildMatrix() const;
};