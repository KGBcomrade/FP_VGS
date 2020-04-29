//
// Created by kgbcomrade on 4/23/20.
//

#ifndef VGS_CONTENTMANAGER_H
#define VGS_CONTENTMANAGER_H

#include <map>
#include <SFML/Graphics.hpp>

using namespace std;

/***
 * A simple way to load a texture
 * @param path name of texture's file
 * @return texture pointer
 */
sf::Texture *contentManagerLoadTexture(char *path);



#endif //VGS_CONTENTMANAGER_H
