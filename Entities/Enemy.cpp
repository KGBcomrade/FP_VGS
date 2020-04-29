//
// Created by kgbcomrade on 4/29/20.
//

#include "Enemy.h"

Enemy::Enemy(sf::Texture *texture, const sf::String &name, sf::Vector2f position, sf::Vector2f size, Level &level) : Entity(texture,
                                                                                                            name,
                                                                                                            position,
                                                                                                            size,
                                                                                                            level) {
    if(name == "EasyEnemy") {
        //sprite.setTextureRect(sf::IntRect(4, 19, size.x, size.y));
        sprite.scale(.5, .5);
        velocity = sf::Vector2f(0, 0);
    }

}

