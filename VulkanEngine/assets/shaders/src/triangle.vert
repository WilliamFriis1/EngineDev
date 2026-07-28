#version 450

struct ObjectData
{
	mat4 model;
	uint materialIndex;
};

layout(binding = 0) uniform CameraData
{
	mat4 view;
	mat4 projection;
} camera;

layout(binding = 1) readonly buffer ObjectBuffer
{
	ObjectData objs[];
} objects;

layout(push_constant) uniform PushData //Ignore error: is in GLSL for Vulkan
{
	uint objectIndex;
} push;

layout(location = 0) in vec2 inPos;
layout(location = 1) in vec3 inColor;

layout(location = 0) out vec3 outColor;
layout(location = 1) flat out uint outMaterialIndex;

void main()
{
    gl_Position = camera.projection * camera.view * objects.objs[push.objectIndex].model * vec4(inPos,0,1);

	outColor = inColor;
	outMaterialIndex = objects.objs[push.objectIndex].materialIndex;
}