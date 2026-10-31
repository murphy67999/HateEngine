#include "Engine.hpp"
#include "Scene.hpp"

namespace
{
    float speed = 25.0f;
    float radius = 1.5f;
}

void ready() {}

void update(float dt)
{
    float time = static_cast<float>(glfwGetTime());

    Scene::objects[0].pointLights[0].position =
        glm::vec3(sin(time), cos(time), 0) * radius;
    Scene::objects[0].meshes[0].transform.position =
        glm::vec3(sin(time), cos(time), 0) * radius;

    Scene::objects[0].pointLights[1].position =
        glm::vec3(cos(time), 0, sin(time)) * radius;
    Scene::objects[0].meshes[1].transform.position =
        glm::vec3(cos(time), 0, sin(time)) * radius;

    Scene::objects[0].pointLights[2].position =
        glm::vec3(cos(time * 0.8f), sin(time * 0.8f), sin(time * 0.8f)) * radius;
    Scene::objects[0].meshes[3].transform.position =
        glm::vec3(cos(time * 0.8f), sin(time * 0.8f), sin(time * 0.8f)) * radius;

    Scene::objects[0].meshes[2].transform.rotation =
        glm::vec3(20 * time, 20 * time, sin(time));

    if (glfwGetKey(Engine::window.getWindow(), GLFW_KEY_S) == GLFW_PRESS)
        Scene::camera.position.z += speed * dt;
    if (glfwGetKey(Engine::window.getWindow(), GLFW_KEY_W) == GLFW_PRESS)
        Scene::camera.position.z -= speed * dt;
}

void end() {}

int main()
{
    Engine::run(ready, update, end);
}