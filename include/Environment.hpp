#pragma once

#include <glm/glm.hpp>

class Environment
{
public:
    glm::vec3 backgroundColor;
    float ambientStrength;

    Environment(glm::vec3 backgroundColor, float ambientStrength)
        : backgroundColor(backgroundColor), ambientStrength(ambientStrength) {}
};