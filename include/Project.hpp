#pragma once

#include <string>
#include "Scene.hpp"

namespace Project
{
    void save(const Scene &scene, const std::string &projectName);
    void load(Scene &scene, const std::string &projectName);
}