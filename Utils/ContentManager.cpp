//
// Created by kgbcomrade on 4/23/20.
//

#include "ContentManager.h"



sf::Texture *contentManagerLoadTexture(char *path) {
    auto tex = new sf::Texture;
    bool res = tex->loadFromFile(path);
    return tex;
}


