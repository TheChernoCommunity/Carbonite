#version 150

const vec2 lightBias = vec2(0.7, 0.6);

in vec3 passNormal;
in vec2 passUV;

out vec4 outColor;

uniform vec3 lightDirection;

uniform samplerCube tex;

uniform float time;

void main(void) {
	vec4 diffuseColor = texture(tex, passNormal);
	vec3 unitNormal = normalize(passNormal);
	float diffuseLight = max(dot(-lightDirection, unitNormal), 0.0) * lightBias.x + lightBias.y;
	outColor = vec4(diffuseColor.xyz * diffuseLight, diffuseColor.w);
}