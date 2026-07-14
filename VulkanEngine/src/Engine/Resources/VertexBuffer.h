#pragma once
#include "Buffer.h"

#include <vulkan/vulkan.h>
#include <glm/glm.hpp>


#include <vector>

struct Vertex
{
	glm::vec2 pos;
	glm::vec3 color;
};

//TEMPORARY, MESHES WILL CONTAIN VERTEX DATA LATER ON
std::vector<Vertex> vertices =
{
    {{ 0.0f, -0.5f }, {1.0f, 0.0f, 0.0f}},
    {{ 0.5f,  0.5f }, {0.0f, 1.0f, 0.0f}},
    {{-0.5f,  0.5f }, {0.0f, 0.0f, 1.0f}}
};

class VertexBuffer
{
private:
    
    Buffer buffer;

public:
    VkBuffer get() const;

    void create(VkPhysicalDevice physicalDevice, VkDevice device);

    void cleanup(VkDevice device);
};