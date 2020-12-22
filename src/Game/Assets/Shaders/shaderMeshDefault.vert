#version 150

in vec3 inPosition;
in vec3 inNormal;
in vec2 inUV;

out vec3 passNormal;
out vec2 passUV;

uniform mat4 transformationMatrix;
uniform mat4 projectionViewMatrix;

void main(void) {
	gl_Position = projectionViewMatrix * transformationMatrix * vec4(inPosition, 1.0);
	passNormal = (transformationMatrix * vec4(inNormal, 0.0)).xyz;
	passUV = inUV;
}