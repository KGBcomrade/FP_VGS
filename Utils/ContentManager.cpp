//
// Created by kgbcomrade on 4/23/20.
//

#include "ContentManager.h"



sf::Texture *contentManagerLoadTexture(const std::string& path) {
    auto tex = new sf::Texture;
    bool res = tex->loadFromFile(path);
    return tex;
}


bool ContentManager::loadTexture(const std::string &key, const std::string& path) {
    auto *tex = new sf::Texture;
    bool res = tex->loadFromFile(path);
    texMap[key] = tex;
    return res;
}

ContentManager::~ContentManager() {
    for(auto &i : texMap)
        delete i.second;
}

sf::Texture *ContentManager::getTexture(const std::string &key) {
    return texMap[key];
}

ContentManager::ContentManager() = default;
