#pragma once

#include <GLFW/glfw3.h>

class Camera;

class Input
{
public:
    void process(GLFWwindow *window, Camera &camera);
};