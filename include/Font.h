//
// Created by Antti Vesanen on 8.7.2022.
//

#ifndef ENGINE_FONT_H
#define ENGINE_FONT_H

#include <SFML/Graphics.hpp>
#include "lua.hpp"

class Font {
private:
    sf::Font font;
public:
    Font();
    ~Font();
    static void l_Register(lua_State *L);
    static int l_new(lua_State *L);
    static int l_free(lua_State *L);
};


#endif //ENGINE_FONT_H
