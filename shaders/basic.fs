#version 330 core

out vec4 fragColor;

uniform vec3 color;
uniform vec3 lightPos;
uniform vec3 lightColor;
uniform float ambientStrength;

in vec3 fragPos;
in vec3 normal;

void main() {
    vec3 ambient = ambientStrength * lightColor;

    vec3 norm = normalize(normal);
    vec3 lightDir = normalize(lightPos - fragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * lightColor;

    vec3 result = (ambient + diffuse) * color;

    fragColor = vec4(result, 1.0);
}