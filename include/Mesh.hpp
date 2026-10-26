#pragma once

#include "Shader.hpp"
#include <glm/gtc/matrix_transform.hpp>

enum MeshType
{
    CUBE,
    PYRAMID
};

class Mesh
{
public:
    MeshType type;
    glm::vec3 position{0.0f};
    glm::vec3 scale{1.0f};
    glm::vec3 color{1.0f};

    Mesh(MeshType type);
    void setup(glm::mat4 view, Shader &shader) const;
};