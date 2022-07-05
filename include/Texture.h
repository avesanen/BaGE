//
// Created by Antti Vesanen on 3.7.2022.
//

#ifndef ENGINE_TEXTURE_H
#define ENGINE_TEXTURE_H

#include <SFML/Graphics.hpp>
#include "lua.hpp"

class Texture : public sf::Drawable, public sf::Transformable {
public:
    Texture(int w, int h);
    bool LoadImage(std::string file);
    void SetPixel(unsigned int x, unsigned int y, sf::Uint8 r, sf::Uint8 g, sf::Uint8 b);
    sf::Color GetPixel(unsigned int x, unsigned int y);
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    void UpdateTexture();
private:
    sf::Image image;
    sf::Texture texture;
    sf::Sprite sprite;
    bool dirty{};
public:
    static void l_Register(lua_State *L);
    static int l_new(lua_State *L);
    static int l_free(lua_State *L);
    static int l_SetPixel(lua_State *L);
    static int l_GetPixel(lua_State *L);
    static int l_LoadFile(lua_State *L);
};


#endif //ENGINE_TEXTURE_H
