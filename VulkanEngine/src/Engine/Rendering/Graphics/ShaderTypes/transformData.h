#pragma once

#include "Engine/Rendering/Graphics/Math/glm.h"

struct TransformData
{
	glm::mat4 model;
	glm::mat4 view;
	glm::mat4 projection;
};