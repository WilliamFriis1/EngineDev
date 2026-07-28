#version 450

struct MaterialData
{
	vec4 baseColor;

	float roughness;
	float metallic;
	float emissiveStrength;
};

layout(binding = 2) readonly buffer MaterialBuffer
{
	MaterialData mat[];
} materials;

layout(location = 0) in vec3 inColor;
layout(location = 1) flat in uint materialIndex;

layout(location = 0) out vec4 outColor;

void main()
{
	outColor = materials.mat[materialIndex].baseColor * vec4(inColor, 1.0);
}