//
// Created by kgbcomrade on 4/29/20.
//

#ifndef FP2_ENEMY_H
#define FP2_ENEMY_H


#include "Entity.h"

class Enemy : public Entity{
public:
    Enemy(sf::Texture * texture, const sf::String& name, sf::Vector2f position, sf::Vector2f size, Level & level);
};


#endif //FP2_ENEMY_H
