#include "Camera.hpp"

#include <glm/gtc/matrix_transform.hpp>

Camera::Camera(glm::vec3 pos, glm::vec3 front, glm::vec3 up) : m_pos(pos), m_front(front), m_up(up) {}

void Camera::moveForward(float dt)
{
    m_pos += m_front * m_speed * dt;
}

void Camera::moveBackward(float dt)
{
    m_pos -= m_front * m_speed * dt;
}

void Camera::moveLeft(float dt)
{
    m_pos -= glm::normalize(glm::cross(m_front, m_up)) * m_speed * dt;
}

void Camera::moveRight(float dt)
{
    m_pos += glm::normalize(glm::cross(m_front, m_up)) * m_speed * dt;
}

glm::mat4 Camera::getLookAt() const
{
    return glm::lookAt(m_pos, m_pos + m_front, m_up);
}