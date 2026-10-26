#pragma once

#include <GLFW/glfw3.h>

class Camera;

namespace Input
{
    void process(float dt);
    void init(GLFWwindow *window, Camera *camera);
}