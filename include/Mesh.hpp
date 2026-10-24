#pragma once

#include "Shader.hpp"
#include <glm/gtc/matrix_transform.hpp>

class Mesh
{
public:
    glm::vec3 position{0.0f};
    glm::vec3 scale{1.0f};
    glm::vec3 color{1.0f};

    void render(glm::mat4 view, Shader &shader) const;
};