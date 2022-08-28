//
// Created by Antti Vesanen on 8.7.2022.
//

#include "Font.h"

int Font::l_new(lua_State *L) {
    *reinterpret_cast<Font**>(lua_newuserdata(L, sizeof(Font*))) = new Font();
    luaL_setmetatable(L, "Font");
    return 1;
}

int Font::l_free(lua_State *L) {
    delete *reinterpret_cast<Font**>(lua_touserdata(L, 1));
    return 0;
}

void Font::l_Register(lua_State *L) {
    lua_register(L, "Font", l_new);
    luaL_newmetatable(L, "Font");
    lua_pushcfunction(L, l_free); lua_setfield(L, -2, "__gc");
    lua_pushvalue(L, -1); lua_setfield(L, -2, "__index");
    lua_pop(L, 1);
}

Font::Font() {
    printf("Font created\n");
}

Font::~Font() {
    printf("Font destroyed\n");
}
