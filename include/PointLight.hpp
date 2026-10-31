#pragma once

#include <glm/glm.hpp>

class PointLight
{
public:
    glm::vec3 position{0.0f, 0.0f, 0.0f};
    glm::vec3 color{1.0f, 1.0f, 1.0f};
    float intensity = 1.0f;
};