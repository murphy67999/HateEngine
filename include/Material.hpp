#pragma once

#include <glm/glm.hpp>

class Material
{
public:
    glm::vec3 color{1.0f};
    glm::vec3 emission{0.0f};
    float specularStrength = 0.5f;
    float shininess = 32.0f;
};