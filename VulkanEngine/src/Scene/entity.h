#pragma once

#include "Transform.h"
#include "Engine/Resources/mesh.h"

class Entity
{
public:
	Transform transform;
	Mesh* mesh;
};