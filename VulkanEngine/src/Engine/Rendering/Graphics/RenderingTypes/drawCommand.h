#pragma once

#include "Engine/Resources/mesh.h"

struct DrawCommand
{
	Mesh* mesh;

	uint32_t objectIndex;
};