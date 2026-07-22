#version 450

layout(binding = 0) uniform TransformData
{
	mat4 model;
} ubo;
layout(location = 0) in vec2 inPos;
layout(location = 1) in vec3 inColor;

layout(location = 0) out vec3 fragColor;

void main()
{
	gl_Position = ubo.model * vec4(inPos, 0.0, 1.0);
	fragColor = inColor;
}