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
		data.materialIndex = entity.mesh->materialIndex;

		objs.push_back(data);
	}
}

void Scene::buildMaterialBuffer(std::vector<MaterialData>& materials)
{
	for (auto& entity : entities)
	{
		if (entity.mesh == nullptr)
			continue;

		MaterialData data;

		data.baseColor = entity.mesh->material.baseColor;
		data.roughness = entity.mesh->material.roughness;
		data.metallic = entity.mesh->material.metallic;
		data.emissiveStrength = entity.mesh->material.emissiveStrength;

		materials.push_back(data);
	}
}
