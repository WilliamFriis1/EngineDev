#pragma once

#include "Engine/Rendering/Graphics/Math/glm.h"

struct ObjectData
{
	glm::mat4 model;
	uint32_t materialIndex;
};