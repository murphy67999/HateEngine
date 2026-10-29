#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <string>

class Window
{
public:
    Window(int width, int height, const std::string &title);
    ~Window();
    bool shouldClose() const;
    void update() const;
    GLFWwindow *getWindow() const;
    bool isValid() const;

private:
    GLFWwindow *m_window = nullptr;
    bool m_isValid = false;
};