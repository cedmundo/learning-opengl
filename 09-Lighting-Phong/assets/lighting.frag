#version 330 core

out vec4 FragColor;

uniform vec3 objectColor;
uniform vec3 lightColor;
uniform float ambientLightStrength;

void main() {
    vec3 ambient = ambientLightStrength * lightColor;

    vec3 result = objectColor * ambient;
    FragColor = vec4(result, 1.0);
}
