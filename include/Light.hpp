#pragma once

#include <glm/glm.hpp>

class Light
{
public:
    glm::vec3 position;
    glm::vec3 color;
    float specularStrength;

    Light(glm::vec3 position, glm::vec3 color, float specularStrength)
        : position(position), color(color), specularStrength(specularStrength) {}
};