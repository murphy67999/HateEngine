#include "Engine.hpp"

#include "Renderer.hpp"
#include "Input.hpp"
#include "Project.hpp"

void Engine::run(
    std::function<void(Window &)> ready,
    std::function<void(float)> update,
    std::function<void()> end,
    std::string projectName) const
{
    Window window(1920, 1080, projectName);
    Renderer renderer;
    Input::init(window.getWindow(), renderer.getCamera());

    Project::load(projectName);

    ready(window);

    float lastFrame = 0.0f;

    while (!window.shouldClose())
    {
        float dt = 0.0f;
        float currentFrame = static_cast<float>(glfwGetTime());
        dt = currentFrame - lastFrame;
        lastFrame = currentFrame;

        Input::process(dt);

        renderer.render();

        update(dt);

        window.update();
    }

    end();
}