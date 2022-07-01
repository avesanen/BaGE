//
// Created by Antti Vesanen on 1.7.2022.
//
#include "Engine.h"

void Engine::Init(lua_State *L) {
}

int Engine::l_SetPixel(lua_State *L) {
    return 0;
}

int Engine::l_GetPixel(lua_State *L) {
    return 0;
}

void Engine::OnKeyUp(lua_State *L, char k) {
}

void Engine::Update(lua_State *L, float d) {
}

void Engine::OnKeyDown(lua_State *L, char k) {
}

void Engine::Run() {
    // SFML
    window.create(sf::VideoMode(660, 500), "Engine");
    window.setFramerateLimit(30);
    window.setKeyRepeatEnabled(false);

    // Lua
    lua_State *L;
    L = luaL_newstate();
    luaL_openlibs(L);

    lua_newtable(L);
    int top = lua_gettop(L);

    lua_pushstring(L, "version");
    lua_pushstring(L, "v0.0.1");
    lua_settable(L, top);

    lua_pushstring(L, "GetPixel");
    lua_pushcfunction(L, Engine::l_GetPixel);
    lua_settable(L, top);

    lua_pushstring(L, "SetPixel");
    lua_pushcfunction(L, Engine::l_SetPixel);
    lua_settable(L, top);

    lua_setglobal(L, "Engine");

    sf::Clock deltaClock;
    Init(L);
    while (window.isOpen()) {
        sf::Event event{};
        while (window.pollEvent(event)) {
            // "close requested" event: we close the window
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::KeyPressed) {
                OnKeyDown(L, event.key.code);
            }
            if (event.type == sf::Event::KeyReleased) {
                OnKeyUp(L, event.key.code);
            }
        }
        float dt = deltaClock.restart().asSeconds();

        Update(L, dt);

        window.clear(sf::Color(64,64,64,255));

        window.display();
    }
}
