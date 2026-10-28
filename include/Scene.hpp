#pragma once

#include <vector>
#include "GameObject.hpp"
#include "Light.hpp"
#include "Environment.hpp"
#include <glm/glm.hpp>

class Scene
{
public:
    std::vector<GameObject> objects;
    Light light{glm::vec3(0.0f), glm::vec3(1.0f), 0.5f};
    Environment environment{glm::vec3(0.0f), 0.5f};
};