#include "renderQueue.h"

const std::vector<DrawCommand>& RenderQueue::get() const
{
	return commands;
}

void RenderQueue::clear()
{
	commands.clear();
}

void RenderQueue::add(const DrawCommand& command)
{
	commands.push_back(command);
}

