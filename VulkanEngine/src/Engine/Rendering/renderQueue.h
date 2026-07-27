#pragma once

#include "Engine/Rendering/Graphics/RenderingTypes/drawCommand.h"

#include <vector>

class RenderQueue
{
private:
	std::vector<DrawCommand> commands;

public:

	const std::vector<DrawCommand>& get() const;

	void clear();

	void add(const DrawCommand& command);

};