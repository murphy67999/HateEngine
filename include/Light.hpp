#pragma once

#include <glm/glm.hpp>

class Light
{
public:
    glm::vec3 pos;
    glm::vec3 color;
    float specularStrength;

    Light(glm::vec3 pos, glm::vec3 color, float specularStrength)
        : pos(pos), color(color), specularStrength(specularStrength) {}
};