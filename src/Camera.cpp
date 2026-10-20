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

void Camera::processMouseMovement(float xOffset, float yOffset)
{
    m_yaw += xOffset * m_sensitivity;
    m_pitch += yOffset * m_sensitivity;

    m_pitch = glm::clamp(m_pitch, -89.0f, 89.0f);

    m_front.x = cos(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));
    m_front.y = sin(glm::radians(m_pitch));
    m_front.z = sin(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));
}