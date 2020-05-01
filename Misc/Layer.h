//
// Created by kgbcomrade on 4/29/20.
//

#ifndef FP2_LAYER_H
#define FP2_LAYER_H


#include <vector>
#include <SFML/Graphics/Sprite.hpp>

struct Layer {
    int opacity;
    std::vector<sf::Sprite*> tiles;
    ~Layer();
};




#endif //FP2_LAYER_H
