#pragma once

#include <string>
#include "Mesh.hpp"
#include "Transform.hpp"
#include "Material.hpp"

class GameObject
{
public:
    std::string name;
    Transform transform;
    Mesh mesh;
    Material material;

    GameObject(const std::string &name, GeometryType type)
        : name(name), mesh(type) {}
};