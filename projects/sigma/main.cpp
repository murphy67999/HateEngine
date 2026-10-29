#include "Engine.hpp"
#include "Scene.hpp"

void ready(Window &window) {}

void update(float dt)
{
    Scene::objects[0].transform.position.x += 0.5 * dt;
}

void end() {}

int main()
{
    Engine engine;
    engine.run(ready, update, end, "sigma");
}