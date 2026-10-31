#include "Engine.hpp"

void ready() {}

void update(float dt) {}

void end() {}

int main()
{
    Engine::run(ready, update, end);
}