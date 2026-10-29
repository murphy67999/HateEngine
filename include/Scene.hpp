#pragma once

#include <vector>
#include "GameObject.hpp"
#include "Light.hpp"
#include "Environment.hpp"
#include <glm/glm.hpp>

namespace Scene
{
    extern std::vector<GameObject> objects;
    extern Light light;
    extern Environment environment;
};