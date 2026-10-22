#include "Input.hpp"

#include "Camera.hpp"

namespace
{
    Camera *cam;
    bool rotateCamera = false;
    bool firstMouse = false;

    void mouseCallBack(GLFWwindow *window, double newX, double newY)
    {
        if (!rotateCamera)
            return;

        static float lastX = 0.0f;
        static float lastY = 0.0f;

        if (firstMouse)
        {
            firstMouse = false;
            lastX = 800.0f;
            lastY = 400.0f;
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

    glfwSetCursorPosCallback(m_window, mouseCallBack);
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

    static bool zWasPressed = false;
    bool zIsPressed = glfwGetKey(m_window, GLFW_KEY_Z) == GLFW_PRESS;
    if (zIsPressed && !zWasPressed)
    {
        rotateCamera = !rotateCamera;
        if (rotateCamera)
        {
            firstMouse = true;
            glfwSetCursorPos(m_window, 800.0, 400.0);
            glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
        }
        else
            glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
    }

    zWasPressed = zIsPressed;
}
