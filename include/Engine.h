//
// Created by Antti Vesanen on 1.7.2022.
//

#ifndef ENGINE_ENGINE_H
#define ENGINE_ENGINE_H

#include <SFML/Graphics.hpp>
#include <lua.hpp>

class Engine {
private:
    Engine() = default;
    sf::RenderWindow window;
    lua_State* L{};
public:
    static Engine& getInstance() {
        static Engine instance;
        return instance;
    }
    Engine(Engine const&) = delete;
    void operator = (Engine const&) = delete;

    void Init();

    // Lua C Functions
    static int l_SetPixel(lua_State *L);
    static int l_GetPixel(lua_State *L);

    // Lua callbacks
    static void Update(lua_State *L, float d);
    static void OnKeyUp(lua_State *L, char k);
    static void OnKeyDown(lua_State *L, char k);
    static void Init(lua_State *L);
};


#endif //ENGINE_ENGINE_H
