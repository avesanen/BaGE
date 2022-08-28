#include <iostream>
#include "Texture.h"

Texture::Texture(int w, int h) {
    image.create(w, h, sf::Color::Black);
}

sf::Color Texture::GetPixel(unsigned int x, unsigned int y) {
    return image.getPixel(x,y);
}

void Texture::SetPixel(unsigned int x, unsigned int y, sf::Uint8 r, sf::Uint8 g, sf::Uint8 b) {
    sf::Color color = sf::Color(r,g,b);
    image.setPixel(x,y,color);
    dirty = true;
}

bool Texture::LoadImage(std::string file) {
    std::cout << "Loading " << file << std::endl;
    if (!image.loadFromFile(file)) {
        return false;
    }
    texture.loadFromImage(image);
    sprite.setTexture(texture);
    return true;
}

void Texture::l_Register(lua_State *L) {
    lua_register(L, "Texture", l_new);
    luaL_newmetatable(L, "Texture");
    lua_pushcfunction(L, l_free); lua_setfield(L, -2, "__gc");
    lua_pushvalue(L, -1); lua_setfield(L, -2, "__index");
    lua_pushcfunction(L, l_GetPixel); lua_setfield(L, -2, "GetPixel");
    lua_pushcfunction(L, l_SetPixel); lua_setfield(L, -2, "SetPixel");
    lua_pushcfunction(L, l_LoadFile); lua_setfield(L, -2, "LoadFile");
    lua_pop(L, 1);
}

int Texture::l_SetPixel(lua_State *L) {
    Texture *texture = *reinterpret_cast<Texture**>(luaL_checkudata(L, 1, "Texture"));
    int x = (int)luaL_checknumber(L, 2);
    int y = (int)luaL_checknumber(L, 3);
    int r = (int)luaL_checknumber(L, 4);
    int g = (int)luaL_checknumber(L, 5);
    int b = (int)luaL_checknumber(L, 6);
    (*texture).SetPixel(x,y,r,g,b);
    return 0;
}

int Texture::l_GetPixel(lua_State *L) {
    Texture *texture = *reinterpret_cast<Texture**>(luaL_checkudata(L, 1, "Texture"));
    int x = (int)luaL_checknumber(L, 2);
    int y = (int)luaL_checknumber(L, 3);
    sf::Color color = (*texture).GetPixel(x,y);
    lua_pushinteger(L, color.r);
    lua_pushinteger(L, color.g);
    lua_pushinteger(L, color.b);
    return 3;
}

int Texture::l_new(lua_State *L) {
    int w = (int)luaL_checknumber(L, 1);
    int h = (int)luaL_checknumber(L, 2);
    *reinterpret_cast<Texture**>(lua_newuserdata(L, sizeof(Texture*))) = new Texture(w,h);
    luaL_setmetatable(L, "Texture");
    return 1;
}

int Texture::l_free(lua_State *L) {
    printf("Texture destroyed\n");
    delete *reinterpret_cast<Texture**>(lua_touserdata(L, 1));
    return 0;
}

void Texture::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    target.draw(sprite, states);
}

int Texture::l_LoadFile(lua_State *L) {
    Texture *texture = *reinterpret_cast<Texture**>(luaL_checkudata(L, 1, "Texture"));
    std::string file = luaL_checkstring(L, 2);
    auto ok = (*texture).LoadImage(file);
    lua_pushboolean(L, ok);
    return 1;
}

void Texture::UpdateTexture() {
    if (dirty) {
        texture.loadFromImage(image);
        sprite.setTexture(texture);
        dirty = false;
    }
}
