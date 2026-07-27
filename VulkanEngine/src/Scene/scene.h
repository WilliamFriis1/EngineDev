#pragma once

#include "Scene/camera.h"
#include "Scene/entity.h"
#include "Engine/Rendering/renderQueue.h"
#include "Engine/Rendering/Graphics/RenderingTypes/objectData.h"

#include <vector>
class Scene
{
public:
	Camera* activeCamera = nullptr;

	std::vector<Entity> entities{};

	void buildRenderQueue(RenderQueue& queue);

	void buildObjectBuffer(std::vector<ObjectData>& objs);
};