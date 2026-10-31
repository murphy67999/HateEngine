#include "Engine.hpp"
#include "Scene.hpp"

namespace
{
    float speed = 10.0f;
}

void ready() {}

void update(float dt)
{
    float finalSpeed = speed * dt;

    if (glfwGetKey(Engine::window.getWindow(), GLFW_KEY_W) == GLFW_PRESS)
    {
        Scene::objects[0].transform.position.y += finalSpeed;
    }
    if (glfwGetKey(Engine::window.getWindow(), GLFW_KEY_S) == GLFW_PRESS)
    {
        Scene::objects[0].transform.position.y -= finalSpeed;
    }
    if (glfwGetKey(Engine::window.getWindow(), GLFW_KEY_A) == GLFW_PRESS)
    {
        Scene::objects[0].transform.position.x -= finalSpeed;
    }

    if (glfwGetKey(Engine::window.getWindow(), GLFW_KEY_D) == GLFW_PRESS)
    {
        Scene::objects[0].transform.position.x += finalSpeed;
    }
}

void end() {}

int main()
{
    Engine::run(ready, update, end);
}