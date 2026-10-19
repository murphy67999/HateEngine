#pragma once

#include "GLFW/glfw3.h"
#include <string>

class Window
{
public:
    bool isValid = false;

    Window(int width, int height, const std::string &title);
    ~Window();
    bool shouldClose() const;
    void update() const;
    GLFWwindow *getWindow() const;

private:
    GLFWwindow *m_ptr_window = nullptr;
};