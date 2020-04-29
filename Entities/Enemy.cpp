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
        sprite.setTextureRect(sf::IntRect(position.x, position.y, position.x + size.x, position.y + size.y));
        velocity = sf::Vector2f(.2, 0);
    }

}

