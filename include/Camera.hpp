#pragma once

#include <glm/glm.hpp>

class Camera
{
public:
    Camera(glm::vec3 pos, glm::vec3 front, glm::vec3 up);
    void moveForward(float dt);
    void moveBackward(float dt);
    void moveLeft(float dt);
    void moveRight(float dt);
    glm::mat4 getLookAt() const;

private:
    glm::vec3 m_pos;
    glm::vec3 m_front;
    glm::vec3 m_up;
    static constexpr float m_speed = 5.0f;
};