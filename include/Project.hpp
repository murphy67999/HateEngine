#pragma once

#include <vector>
#include "Mesh.hpp"
#include <glm/glm.hpp>
#include <string>

namespace Project
{
    void save(const std::vector<Mesh> &meshes, const glm::vec3 &backgroundColor, const std::string &projectName);
    void load(std::vector<Mesh> &meshes, glm::vec3 &backgroundColor, std::string &projectName);
}