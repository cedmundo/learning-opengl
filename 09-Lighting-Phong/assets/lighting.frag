#version 330 core
in vec3 Normal;
in vec3 FragPos;
out vec4 FragColor;

uniform float objectShiness;
uniform vec3 objectColor;
uniform vec3 viewPos;
uniform vec3 lightPos;
uniform vec3 lightColor;
uniform float ambientLightStrength;
uniform float spectacularStrength;

void main() {
    // ambient
    vec3 ambient = ambientLightStrength * lightColor;

    // diffuse
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(lightPos - FragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * lightColor;

    // spectacular
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), objectShiness);
    vec3 spectacular = spectacularStrength * spec * lightColor;

    vec3 result = (ambient + diffuse + spectacular) * objectColor;
    FragColor = vec4(result, 1.0);
}
