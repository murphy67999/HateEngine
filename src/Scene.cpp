#include "Scene.hpp"

namespace Scene
{
    std::vector<GameObject> objects;
    Environment environment(glm::vec3(0.0f), 0.5f);
    Camera camera;
}