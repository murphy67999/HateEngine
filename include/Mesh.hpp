#pragma once

#include "Shader.hpp"
#include <glm/glm.hpp>

enum class GeometryType
{
    CUBE,
    PYRAMID,
    OCTAHEDRON
};

class Mesh
{
public:
    glm::vec3 position{0.0f};
    glm::vec3 scale{1.0f};
    glm::vec3 color{1.0f};

    Mesh(GeometryType type);
    void update(const Shader &shader) const;
    GeometryType getType() const;

private:
    GeometryType m_type;
};