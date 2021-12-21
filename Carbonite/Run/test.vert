#version 450

layout(location = 0) in vec4 inPosition;
layout(location = 1) in vec4 inNormal;
layout(location = 2) in vec2 inUV;

layout(location = 0) out vec2 outUV;

layout(set = 0, binding = 0) uniform Matrices {
	mat4 model;
	mat4 projView;
} matrices;

void main() {
	vec4 worldPosition = matrices.model * inPosition;
	gl_Position = matrices.projView * worldPosition;
	outUV = inUV;
}