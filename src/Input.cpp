#include "Input.hpp"

#include "Camera.hpp"

namespace
{
    Camera *cam;

    void mouseCallBack(GLFWwindow *window, double xPos, double yPos)
    {
        static float lastX = 0.0f;
        static float lastY = 0.0f;
        static bool firstMouse = true;

        float newX = static_cast<float>(xPos);
        float newY = static_cast<float>(yPos);

        if (firstMouse)
        {
            lastX = newX;
            lastY = newY;
            firstMouse = false;
            return;
        }

        float xOffset = newX - lastX;
        float yOffset = lastY - newY;
        lastX = newX;
        lastY = newY;

        cam->processMouseMovement(xOffset, yOffset);
    };
}

Input::Input(GLFWwindow *window, Camera &camera)
    : m_window(window), m_camera(camera)
{
    cam = &camera;

    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glfwSetCursorPosCallback(window, mouseCallBack);
}

void Input::process(float dt)
{
    if (glfwGetKey(m_window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(m_window, true);

    if (glfwGetKey(m_window, GLFW_KEY_W) == GLFW_PRESS)
        m_camera.moveForward(dt);
    if (glfwGetKey(m_window, GLFW_KEY_S) == GLFW_PRESS)
        m_camera.moveBackward(dt);
    if (glfwGetKey(m_window, GLFW_KEY_A) == GLFW_PRESS)
        m_camera.moveLeft(dt);
    if (glfwGetKey(m_window, GLFW_KEY_D) == GLFW_PRESS)
        m_camera.moveRight(dt);
}
