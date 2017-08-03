#version 330 core
in vec3 Normal;
in vec3 FragPos;
in vec2 TexCoords;
out vec4 FragColor;

struct Material {
    sampler2D   diffuse;
    sampler2D   specular;
    sampler2D   emission;
    float       shininess;
    float       emitStrength;
};

struct DirectionalLight {
    vec3 direction;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

struct PointLight {
    vec3 position;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;

    float constant;
    float linear;
    float quadratic;
};

struct SpotLight {
    vec3 position;
    vec3 direction;
    float cutOff;
    float outerCutOff;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;

    float constant;
    float linear;
    float quadratic;
};

uniform Material material;
uniform DirectionalLight dLight;
uniform PointLight pLight;
uniform SpotLight sLight;
uniform vec3 viewPos;
uniform int lightSource;

void main() {
    vec3 norm = normalize(Normal);

    // DirectionalLight
    if (lightSource == 0) {
        vec3 viewDir    = normalize(viewPos - FragPos);
        vec3 lightDir   = normalize(-dLight.direction);
        vec3 reflectDir = reflect(-lightDir, norm);

        float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
        float diff = max(dot(norm, lightDir), 0.0);

        vec3 ambient  = dLight.ambient  * vec3(texture(material.diffuse, TexCoords));
        vec3 diffuse  = dLight.diffuse  * diff * vec3(texture(material.diffuse, TexCoords));
        vec3 specular = dLight.specular * spec * vec3(texture(material.specular, TexCoords));
        vec3 emission = max(material.emitStrength, 0.0) * vec3(texture(material.emission, TexCoords));

        FragColor = vec4(ambient + diffuse + specular + emission, 1.0);

    // PointLight
    } else if (lightSource == 1) {
        float distance      = length(pLight.position - FragPos);
        float attenuation   = 1.0 / (pLight.constant + pLight.linear * distance + pLight.quadratic * (distance * distance));

        vec3 viewDir    = normalize(viewPos - FragPos);
        vec3 lightDir   = normalize(pLight.position - FragPos);
        vec3 reflectDir = reflect(-lightDir, norm);

        float spec      = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
        float diff      = max(dot(norm, lightDir), 0.0);

        vec3 ambient  = pLight.ambient  * vec3(texture(material.diffuse, TexCoords)) * attenuation;
        vec3 diffuse  = pLight.diffuse  * diff * vec3(texture(material.diffuse, TexCoords)) * attenuation;
        vec3 specular = pLight.specular * spec * vec3(texture(material.specular, TexCoords)) * attenuation;
        vec3 emission = max(material.emitStrength, 0.0) * vec3(texture(material.emission, TexCoords));

        FragColor = vec4(ambient + diffuse + specular + emission, 1.0);

    // SpotLight
    } else if (lightSource == 2) {
        // ambient
        vec3 ambient = sLight.ambient * texture(material.diffuse, TexCoords).rgb;

        // diffuse
        vec3 norm = normalize(Normal);
        vec3 lightDir = normalize(sLight.position - FragPos);
        float diff = max(dot(norm, lightDir), 0.0);
        vec3 diffuse = sLight.diffuse * diff * texture(material.diffuse, TexCoords).rgb;

        // specular
        vec3 viewDir = normalize(viewPos - FragPos);
        vec3 reflectDir = reflect(-lightDir, norm);
        float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
        vec3 specular = sLight.specular * spec * texture(material.specular, TexCoords).rgb;

        // spotlight (soft edges)
        float theta = dot(lightDir, normalize(-sLight.direction));
        float epsilon = (sLight.cutOff - sLight.outerCutOff);
        float intensity = clamp((theta - sLight.outerCutOff) / epsilon, 0.0, 1.0);
        diffuse  *= intensity;
        specular *= intensity;

        // attenuation
        float distance    = length(sLight.position - FragPos);
        float attenuation = 1.0 / (sLight.constant + sLight.linear * distance + sLight.quadratic * (distance * distance));
        ambient  *= attenuation;
        diffuse   *= attenuation;
        specular *= attenuation;

        vec3 result = ambient + diffuse + specular;
        FragColor = vec4(result, 1.0);
    }
}
