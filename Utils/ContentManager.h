//
// Created by kgbcomrade on 4/23/20.
//

#ifndef VGS_CONTENTMANAGER_H
#define VGS_CONTENTMANAGER_H

#include <map>
#include <SFML/Graphics.hpp>


class ContentManager {
private:
    std::map<std::string, sf::Texture*> texMap;
public:
    ContentManager();
    ~ContentManager();
    bool loadTexture(const std::string &key, const std::string& path);
    sf::Texture* getTexture(const std::string &key);

};



#endif //VGS_CONTENTMANAGER_H
