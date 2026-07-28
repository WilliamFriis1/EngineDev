#pragma once
#include "texture.h"
#include "Engine/Rendering/Graphics/Math/glm.h"

class Material
{
public:

	Texture* albedo = nullptr;
	Texture* normal = nullptr;
	Texture* orm = nullptr;
	Texture* emissive = nullptr;

	glm::vec4 baseColor{ 1.0f, 0.0f, 0.0f, 1.0f };

	float metallic = 1.0f;
	float roughness = 1.0f;
	float emissiveStrength = 1.0f;
};