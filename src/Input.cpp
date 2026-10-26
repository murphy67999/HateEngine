#include "Input.hpp"

#include "Camera.hpp"

namespace
{
    GLFWwindow *n_window = nullptr;
    Camera *n_camera = nullptr;

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

        n_camera->processMouseMovement(xOffset, yOffset);
    };
}

namespace Input
{
    void init(GLFWwindow *window, Camera *camera)
    {
        n_window = window;
        n_camera = camera;

        glfwSetCursorPosCallback(window, mouseCallBack);
    }

    void process(float dt)
    {
        if (glfwGetKey(n_window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
            glfwSetWindowShouldClose(n_window, true);

        if (glfwGetKey(n_window, GLFW_KEY_W) == GLFW_PRESS)
            n_camera->moveForward(dt);
        if (glfwGetKey(n_window, GLFW_KEY_S) == GLFW_PRESS)
            n_camera->moveBackward(dt);
        if (glfwGetKey(n_window, GLFW_KEY_A) == GLFW_PRESS)
            n_camera->moveLeft(dt);
        if (glfwGetKey(n_window, GLFW_KEY_D) == GLFW_PRESS)
            n_camera->moveRight(dt);

        static bool zWasPressed = false;
        bool zIsPressed = glfwGetKey(n_window, GLFW_KEY_Z) == GLFW_PRESS;
        if (zIsPressed && !zWasPressed)
        {
            rotateCamera = !rotateCamera;
            if (rotateCamera)
            {
                firstMouse = true;
                glfwSetCursorPos(n_window, 800.0, 400.0);
                glfwSetInputMode(n_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
            }
            else
                glfwSetInputMode(n_window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
        }

        zWasPressed = zIsPressed;
    }

}
