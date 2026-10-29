#pragma once

#include <functional>
#include <string>

#include "Window.hpp"

class Engine
{
public:
    void run(
        std::function<void(Window &)> ready,
        std::function<void(float)> update,
        std::function<void()> end,
        std::string projectName) const;
};