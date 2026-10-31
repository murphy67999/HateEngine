#pragma once

#include "Window.hpp"
#include "Renderer.hpp"
#include <functional>
#include <string>

namespace Engine
{
    extern Window window;
    extern Renderer renderer;

    void run(
        std::function<void()> ready,
        std::function<void(float)> update,
        std::function<void()> end);
}