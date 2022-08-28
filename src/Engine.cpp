//
// Created by Antti Vesanen on 1.7.2022.
//
#include <iostream>
#include "Engine.h"
#include "Texture.h"
#include "Font.h"

void Engine::Init(lua_State *L) {
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

int Engine::l_Draw(lua_State *L) {
    //Engine *engine = static_cast<Engine*>(lua_touserdata(L, 1));
    Texture *tex = *reinterpret_cast<Texture**>(luaL_checkudata(L, 2, "Texture"));
    auto x = (float)luaL_checkinteger(L, 3);
    auto y = (float)luaL_checkinteger(L, 4);
    auto t = sf::Transform();
    t.translate(x, y);
    tex->UpdateTexture();
    getInstance().window.draw(*tex, t);
    return 0;
}

sf::View getLetterboxView(sf::View view, float windowWidth, float windowHeight) {
    float windowRatio = windowWidth / windowHeight;
    float viewRatio = view.getSize().x / (float) view.getSize().y;
    float sizeX = 1;
    float sizeY = 1;
    float posX = 0;
    float posY = 0;

    bool horizontalSpacing = true;
    if (windowRatio < viewRatio)
        horizontalSpacing = false;
    if (horizontalSpacing) {
        sizeX = viewRatio / windowRatio;
        posX = (1 - sizeX) / 2.f;
    }
    else {
        sizeY = windowRatio / viewRatio;
        posY = (1 - sizeY) / 2.f;
    }
    view.setViewport( sf::FloatRect(posX, posY, sizeX, sizeY) );
    return view;
}

void Engine::Run(const char* file) {
    screen.create(320, 180, sf::Color::Black);
    window.create(sf::VideoMode(640, 360), "Engine");
    window.setVerticalSyncEnabled(true);
    window.setKeyRepeatEnabled(false);

    // Lua Init
    lua_State *L;
    L = luaL_newstate();
    luaL_openlibs(L);
    Texture::l_Register(L);
    Font::l_Register(L);

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

    lua_pushstring(L, "Draw");
    lua_pushcfunction(L, Engine::l_Draw);
    lua_settable(L, top);

    lua_setglobal(L, "Engine");

    if(luaL_dofile(L, file))
        std::cerr << lua_tostring(L, -1);

    // Main engine loop
    sf::Clock deltaClock;

    sf::View view = window.getView();
    view.zoom(0.5f);
    view.move(-160,-90);

    Init(L);
    deltaClock.restart();
    while (window.isOpen()) {
        sf::Event event{};
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            if (event.type == sf::Event::KeyPressed) {
                OnKeyDown(L, event.key.code);
            }
            if (event.type == sf::Event::KeyReleased) {
                OnKeyUp(L, event.key.code);
            }
            if (event.type == sf::Event::Resized) {
                view = getLetterboxView(view, (float)event.size.width, (float)event.size.height);
            }
        }

        float dt = deltaClock.restart().asSeconds();

        window.clear(sf::Color::Black);
        window.setView(view);

        Update(L, dt);

        window.display();
    }
    lua_close(L);
}
