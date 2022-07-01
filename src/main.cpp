#include "Engine.h"

int main() {
    Engine *engine = &Engine::getInstance();
    engine->Run("snek.lua");
    return 0;
}
