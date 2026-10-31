#include "Camera.hpp"

#include <glm/gtc/matrix_transform.hpp>

glm::mat4 Camera::getProjectionMatrix() const
{
    return glm::perspective(glm::radians(45.0f), 1920.0f / 1080.0f, 0.1f, 100.0f);
}

glm::mat4 Camera::getViewMatrix() const
{
    return glm::lookAt(position, position + direction, up);
}
