#version 330

in vec3 inPosition;
in vec3 inNormal;
in vec2 inUV;

uniform mat4 transformationMatrix;
uniform mat4 projectionViewMatrix;

void main(void) {
	gl_Position = projectionViewMatrix * transformationMatrix * vec4(inPosition, 1.0);
}