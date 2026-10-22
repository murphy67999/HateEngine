#include <glad/glad.h>

#include "Window.hpp"

void framebuffer_size_callback(GLFWwindow *ptr_window, int width, int height)
{
    glViewport(0, 0, width, height);
}

Window::Window(int width, int height, const std::string &title)
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    m_window = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);

    if (!m_window)
    {
        isValid = false;
        return;
    }

    glfwMakeContextCurrent(m_window);
    glfwSwapInterval(0);
    glfwSetFramebufferSizeCallback(m_window, framebuffer_size_callback);

    if ((!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)))
    {
        isValid = false;
        return;
    }

    isValid = true;
}

Window::~Window()
{
    glfwDestroyWindow(m_window);
    glfwTerminate();
}

bool Window::shouldClose() const
{
    return glfwWindowShouldClose(m_window);
}

void Window::update() const
{
    glfwSwapBuffers(m_window);
    glfwPollEvents();
}

GLFWwindow *Window::getWindow() const
{
    return m_window;
}