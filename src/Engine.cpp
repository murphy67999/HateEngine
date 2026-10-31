#include "Engine.hpp"

#include "Project.hpp"
#include <filesystem>
#include "Scene.hpp"

namespace Engine
{
    Window window(1920, 1080, "YOUR_TITLE");
    Renderer renderer;

    void run(
        std::function<void()> ready,
        std::function<void(float)> update,
        std::function<void()> end)
    {
        std::string projectName = std::filesystem::read_symlink("/proc/self/exe").filename().string();
        Project::load(projectName);

        ready();

        float lastFrame = 0.0f;

        while (!window.shouldClose())
        {
            float dt = 0.0f;
            float currentFrame = static_cast<float>(glfwGetTime());
            dt = currentFrame - lastFrame;
            lastFrame = currentFrame;

            renderer.render(Scene::camera);

            update(dt);

            window.update();
        }

        end();
    }
}
