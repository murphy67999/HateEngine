#pragma once

#include <vector>
#include "GameObject.hpp"
#include "Light.hpp"
#include "Environment.hpp"
#include <glm/glm.hpp>
#include "Camera.hpp"

namespace Scene
{
    extern std::vector<GameObject> objects;
    extern Light light;
    extern Environment environment;
    extern Camera camera;
};