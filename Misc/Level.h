//
// Created by kgbcomrade on 4/29/20.
//

#ifndef FP2_LEVEL_H
#define FP2_LEVEL_H


#include <SFML/System.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include "Object.h"
#include "Layer.h"

class Level {
private:
    sf::Vector2i size, tileSize;
    int firstTileID;
    sf::Rect<float> *drawingBounds;
    sf::Texture *tileSetImage;
    std::vector<Object*> objects;
    std::vector<Layer*> layers;
public:
    ~Level();
    bool loadFromFile(const std::string& filename);
    Object *getObject(const std::string& name);
    std::vector<Object*> getObjects(const std::string& name);
    std::vector<Object*> getAllObjects();
    void draw(sf::RenderWindow& window);
    sf::Vector2i getTileSize();
};


#endif //FP2_LEVEL_H
