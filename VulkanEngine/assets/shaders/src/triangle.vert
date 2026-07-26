#version 450

layout(binding = 0) uniform CameraData
{
	mat4 view;
	mat4 projection;
} camera;

layout(binding = 1) readonly buffer ObjectBuffer
{
	mat4 models[];
} objects;

layout(push_constant) uniform PushData
{
	uint objectIndex;
} push;

layout(location = 0) in vec2 inPos;
layout(location = 1) in vec3 inColor;

layout(location = 0) out vec3 fragColor;

void main()
{
    gl_Position = camera.projection * camera.view * objects.models[push.objectIndex] * vec4(inPos,0,1);
	fragColor = inColor;
}