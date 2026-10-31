#pragma once

#include <string>
#include "Transform.hpp"
#include "Mesh.hpp"
#include <vector>
#include "PointLight.hpp"

class GameObject
{
public:
    std::string name;
    Transform transform;
    std::vector<Mesh> meshes;
    std::vector<PointLight> pointLights;

    GameObject(const std::string &name)
        : name(name) {};
};