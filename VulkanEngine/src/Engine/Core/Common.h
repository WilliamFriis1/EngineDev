#pragma once

#include <vulkan/vulkan.h>
#include <glm/glm.hpp>

#include <array>

struct Vertex
{
	glm::vec2 pos;
	glm::vec3 color;

	static VkVertexInputBindingDescription getBindingDesription()
	{
		VkVertexInputBindingDescription bindingDesription{};

		bindingDesription.binding = 0;
		bindingDesription.stride = sizeof(Vertex);
		bindingDesription.inputRate = VK_VERTEX_INPUT_RATE_VERTEX;

		return bindingDesription;
	}

	static std::array<VkVertexInputAttributeDescription, 2> getAttributeDescriptions()
	{
		std::array<VkVertexInputAttributeDescription, 2> attributes{};

		attributes[0].binding = 0;
		attributes[0].location = 0;
		attributes[0].format = VK_FORMAT_R32G32_SFLOAT;
		attributes[0].offset = offsetof(Vertex, pos);

		attributes[1].binding = 0;
		attributes[1].location = 1;
		attributes[1].format = VK_FORMAT_R32G32B32_SFLOAT;
		attributes[1].offset = offsetof(Vertex, color);

		return attributes;
	}
};