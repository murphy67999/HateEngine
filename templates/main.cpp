#include "Engine.hpp"

void ready(Window &window) {}

void update(float dt) {}

void end() {}

int main()
{
    Engine engine;
    engine.run(ready, update, end, "PROJECT_NAME");
}