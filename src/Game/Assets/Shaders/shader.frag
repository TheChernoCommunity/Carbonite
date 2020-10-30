#version 150

const vec2 lightBias = vec2(0.7, 0.6);

in vec3 passNormal;
in vec2 passUV;

out vec4 outColor;

uniform vec3 lightDirection;

void main(void) {
	vec4 diffuseColor = vec4(0.0, 0.513, 1.0, 1.0);
	vec3 unitNormal = normalize(passNormal);
	float diffuseLight = max(dot(-lightDirection, unitNormal), 0.0) * lightBias.x + lightBias.y;
	outColor = vec4(diffuseColor.xyz * diffuseLight, diffuseColor.w);
}