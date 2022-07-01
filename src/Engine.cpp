//
// Created by Antti Vesanen on 1.7.2022.
//
#include "Engine.h"

void Engine::Init() {
    // SFML
    window.create(sf::VideoMode(660, 500), "Engine");
    window.setFramerateLimit(30);
    window.setKeyRepeatEnabled(false);

    // Lua
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

void Engine::Init(lua_State *L) {

}

