#pragma once

#include <vector>
#include <glm/glm.hpp>
#include <string>

#include "Mesh.hpp"
#include "Light.hpp"
#include "Environment.hpp"

namespace Project
{
    void save(const Light &light, const Environment &environment, const std::vector<Mesh> &meshes, const std::string &projectName);
    void load(Light &light, Environment &environment, std::vector<Mesh> &meshes, std::string &projectName);
}