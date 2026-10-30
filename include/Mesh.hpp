#pragma once

enum class GeometryType
{
    CUBE,
    PYRAMID,
    OCTAHEDRON
};

#include "Material.hpp"
#include "Transform.hpp"

class Mesh
{
public:
    Material material;
    Transform transform;

    Mesh(GeometryType type);
    GeometryType getType() const;

private:
    GeometryType m_type;
};