#include "Scene.hpp"

namespace Scene{
    std::vector<GameObject> objects;
    Light light(glm::vec3(0.0f), glm::vec3(1.0f), 0.5f);
    Environment environment(glm::vec3(0.0f), 0.5f);
}