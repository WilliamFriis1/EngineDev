#include "assetLoader.h"
#include "Engine/Rendering/Graphics/VertexTypes/vertex.h"

std::vector<char> AssetLoader::readFile(const std::string& filename)
{
    std::ifstream file(filename, std::ios::ate | std::ios::binary);

    if (!file.is_open())
        throw std::runtime_error("Failed to open shader file: " + filename);

    size_t fileSize = (size_t)file.tellg();
    std::vector<char> buffer(fileSize);

    file.seekg(0);
    file.read(buffer.data(), fileSize);

    file.close();
    return buffer;
}

VkShaderModule AssetLoader::createShaderModule(VkDevice device, const std::vector<char>& code)
{
    VkShaderModuleCreateInfo createInfo{};

    createInfo.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
    createInfo.codeSize = code.size();
    createInfo.pCode = reinterpret_cast<const uint32_t*>(code.data());

    VkShaderModule shaderModule;
    if (vkCreateShaderModule(device, &createInfo, nullptr, &shaderModule) != VK_SUCCESS)
        throw std::runtime_error("Failed to create shader module");

    return shaderModule;
}

std::vector<Vertex> AssetLoader::readObj(const std::string& filename)
{
    std::vector<Vertex> vertices{};

    std::ifstream file(filename);

    if (!file.is_open())
        throw std::runtime_error("Failed to open obj file: " + filename);

    std::string line;

    while (std::getline(file, line))
    {
        
        uint32_t pos = 0;
        char* end_x;
        char* end_y;



        if (line[0] == '#' || line[0] == 'm' || line[0] == 'o')
            continue;

        if(line[0] == 'v')
        { 
            if (line[1] == 'n')
            {
                //normals
                continue;
            }
            else if(line[1] == 't')
            {
                //uvs
                continue;
            }

            Vertex vert{};
      
            pos = line.find(' ', pos);

            vert.pos.x = strtof(&line.at(pos), &end_x);
            vert.pos.y = strtof(end_x, &end_y);
            //vert.pos.z = strtof(end, NULL);

            //Need to fix faces for indexing

            vertices.push_back(vert);
        }
    }
    file.close();

    return vertices;
}