#pragma once

#include <glm/glm.hpp>

class Camera
{
public:
    glm::vec3 position{0.0f, 0.0f, 3.0f};
    glm::vec3 direction{0.0f, 0.0f, -1.0f};
    glm::vec3 up{0.0f, 1.0f, 0.0f};

    glm::mat4 getProjectionMatrix() const;
    glm::mat4 getViewMatrix() const;
};
