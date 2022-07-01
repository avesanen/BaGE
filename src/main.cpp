#include <iostream>
#include "Engine.h"

int main() {
    std::cout << "Hello, World!" << std::endl;

    // Get Engine singleton
    Engine *engine = &Engine::getInstance();

    engine->Run("snek.lua");
    return 0;
}
