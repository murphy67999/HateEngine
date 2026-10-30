#pragma once

#include <string>
#include "Transform.hpp"
#include "Mesh.hpp"
#include <vector>

class GameObject
{
public:
    std::string name;
    Transform transform;
    std::vector<Mesh> meshes;

    GameObject(const std::string &name)
        : name(name) {}
};