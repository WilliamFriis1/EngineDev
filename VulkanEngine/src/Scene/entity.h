#pragma once

#include "Transform.h"
#include "Engine/Resources/mesh.h"

class Entity
{
private:
	uint32_t objectIndex;
public:
	Transform transform{};

	Mesh* mesh = nullptr;

	void init(uint32_t id);

	const uint32_t& getObjectIndex() const;
};