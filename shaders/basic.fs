#version 330 core

out vec4 fragColor;

struct PointLight {
    vec3 position;
    vec3 color;
    float intensity;
};

uniform PointLight pointLights[10];
uniform int pointLightCount;

uniform vec3 color;
uniform vec3 emission;
uniform float specularStrength;
uniform float shininess;

uniform float ambientStrength;
uniform vec3 viewPos;

in vec3 fragPos;
in vec3 normal;

void main() {
    vec3 norm = normalize(normal);
    vec3 viewDir = normalize(viewPos - fragPos);
    vec3 ambient = ambientStrength * color;
    vec3 diffuse = vec3(0.0);
    vec3 specular = vec3(0.0);

    for(int i = 0; i < pointLightCount; i++) {
        vec3 lightDir = normalize(pointLights[i].position - fragPos);
        vec3 radiance = pointLights[i].color * pointLights[i].intensity;

        float diff = max(dot(norm, lightDir), 0.0);
        diffuse += diff * radiance;

        if(diff > 0.0) {
            vec3 reflectDir = reflect(-lightDir, norm);
            float spec = pow(max(dot(viewDir, reflectDir), 0.0), shininess);

            specular += specularStrength * spec * radiance;
        }
    }

    vec3 result = (ambient + diffuse) * color + specular + emission;

    fragColor = vec4(result, 1.0);
}