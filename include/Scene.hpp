#pragma once

#include <vector>
#include "GameObject.hpp"
#include "Environment.hpp"
#include <glm/glm.hpp>
#include "Camera.hpp"

namespace Scene
{
    extern std::vector<GameObject> objects;
    extern Environment environment;
    extern Camera camera;
};