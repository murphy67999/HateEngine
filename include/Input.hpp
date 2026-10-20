#pragma once

#include <GLFW/glfw3.h>

class Camera;

class Input
{
public:
    Input(GLFWwindow *window, Camera &camera);
    void process(float dt);

private:
    GLFWwindow *m_window;
    Camera &m_camera;
};