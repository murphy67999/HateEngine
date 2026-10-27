#pragma once

#include "Shader.hpp"
#include <glm/gtc/matrix_transform.hpp>

enum class GeometryType
{
    CUBE,
    PYRAMID
};

class Mesh
{
public:
    glm::vec3 position{0.0f};
    glm::vec3 scale{1.0f};
    glm::vec3 color{1.0f};

    Mesh(GeometryType type);
    void update(glm::mat4 view, Shader &shader) const;
    GeometryType getType() const;

private:
    GeometryType m_type;
};