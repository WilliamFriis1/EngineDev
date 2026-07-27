#include "scene.h"

void Scene::buildRenderQueue(RenderQueue& queue)
{
	queue.clear();

	for (auto& entity : entities)
	{
		if (entity.mesh == nullptr)
			continue;

		DrawCommand cmd;

		cmd.mesh = entity.mesh;
		cmd.objectIndex = entity.getObjectIndex();

		queue.add(cmd);
	}
}

void Scene::buildObjectBuffer(std::vector<ObjectData>& objs)
{
	for (auto& entity : entities)
	{
		if (entity.mesh == nullptr)
			continue;

		ObjectData data;
		
		data.model = entity.transform.getMatrix();

		objs.push_back(data);
	}
}
