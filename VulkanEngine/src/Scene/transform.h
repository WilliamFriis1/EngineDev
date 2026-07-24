#pragma once

#include "Engine/Rendering/Graphics/Math/glm.h"

class Transform
{
private:
	glm::vec3 position{};
	glm::quat rotation = glm::identity<glm::quat>();
	glm::vec3 transformScale{ 1.0f };

public:
	const glm::mat4 getMatrix() const;

	void translate(glm::vec3 newPosition);
	void rotate(glm::quat newRotation);
	void scale(glm::vec3 newRotation);

};