#include <iostream>
#include "Engine.h"

int main() {
    std::cout << "Hello, World!" << std::endl;

    Engine *engine = &Engine::getInstance();
    engine->Init();
    return 0;
}
