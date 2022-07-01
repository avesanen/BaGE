//
// Created by Antti Vesanen on 1.7.2022.
//
#include <iostream>
#include "Engine.h"

void Engine::Init(lua_State *L) {
    getInstance().screen.create(320, 240, sf::Color::Black);
    getInstance().window.create(sf::VideoMode(660, 500), "Engine");
    getInstance().window.setFramerateLimit(10);
    lua_getglobal(L, "Engine");
    if (!lua_istable(L, -1)) { return; }
    lua_getfield(L, -1, "Init");
    if (!lua_isfunction(L, -1)) { return; }
    lua_pushvalue(L, -2);
    lua_pcall(L, 1,0,0);
}

int Engine::l_SetPixel(lua_State *L) {
    //auto engine = static_cast<Engine*>(lua_touserdata(L, 1));
    auto x = (unsigned int)luaL_checknumber(L, 2);
    auto y = (unsigned int)luaL_checknumber(L, 3);
    auto r = (sf::Uint8)luaL_checknumber(L, 4);
    auto g = (sf::Uint8)luaL_checknumber(L, 5);
    auto b = (sf::Uint8)luaL_checknumber(L, 6);
    getInstance().screen.setPixel(x, y, sf::Color(r,g,b));
    return 0;
}

int Engine::l_GetPixel(lua_State *L) {
    //auto engine = static_cast<Engine*>(lua_touserdata(L, 1));
    auto x = (unsigned int)luaL_checknumber(L, 2);
    auto y = (unsigned int)luaL_checknumber(L, 3);
    sf::Color color = getInstance().screen.getPixel(x, y);
    lua_pushinteger(L, color.r);
    lua_pushinteger(L, color.g);
    lua_pushinteger(L, color.b);
    return 3;
}

void Engine::OnKeyDown(lua_State *L, char k) {
    lua_getglobal(L, "Engine");
    if (!lua_istable(L, -1)) { return; }
    lua_getfield(L, -1, "OnKeyDown");
    if (!lua_isfunction(L, -1)) { return; }
    lua_pushvalue(L, -2);
    lua_pushinteger(L, k);
    lua_pcall(L, 2,0,0);
}

void Engine::OnKeyUp(lua_State *L, char k) {
    lua_getglobal(L, "Engine");
    if (!lua_istable(L, -1)) { return; }
    lua_getfield(L, -1, "OnKeyUp");
    if (!lua_isfunction(L, -1)) { return; }
    lua_pushvalue(L, -2);
    lua_pushinteger(L, k);
    lua_pcall(L, 2,0,0);
}

void Engine::Update(lua_State *L, float d) {
    lua_getglobal(L, "Engine");
    if (!lua_istable(L, -1)) { return; }
    lua_getfield(L, -1, "Update");
    if (!lua_isfunction(L, -1)) { return; }

    lua_pushvalue(L, -2);
    lua_pushnumber(L, d);
    lua_pcall(L, 2,0,0);
}

void Engine::Run(const char* file) {
    // SFML Init
    window.create(sf::VideoMode(660, 500), "Engine");
    window.setFramerateLimit(30);
    window.setKeyRepeatEnabled(false);

    // Lua Init
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


    if(luaL_dofile(L, file))
        std::cerr << lua_tostring(L, -1);

    // Main engine loop
    sf::Clock deltaClock;
    sf::Texture screenTex;
    sf::Sprite screenSpr;
    screenSpr.setScale(2,2);
    screenSpr.setPosition(10,10);
    Init(L);
    while (window.isOpen()) {
        sf::Event event{};
        while (window.pollEvent(event)) {
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

        screenTex.loadFromImage(screen);
        screenSpr.setTexture(screenTex);
        window.clear(sf::Color(64,64,64,255));
        window.draw(screenSpr);
        window.display();
    }
    lua_close(L);
}
