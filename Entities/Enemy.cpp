//
// Created by kgbcomrade on 4/29/20.
//

#include <Utils/Utils.h>
#include "Enemy.h"

Enemy::Enemy(sf::Texture *texture, const sf::String &name, sf::Vector2f position, sf::Vector2f size, Level &level, Player *player) : Entity(texture,
                                                                                                            name,
                                                                                                            position,
                                                                                                            size,
                                                                                                            level) {
    this->player = player;
    if(name == "EasyEnemy") {
        //sprite.setTextureRect(sf::IntRect(4, 19, size.x, size.y));
        sprite->scale(.5, .5);
        velocity = sf::Vector2f(0, 0);
    }

}

void Enemy::update(float dt) {
    sf::Vector2f distance = player->getPosition() - position;
    if(vectorLen(distance) > 50)
        velocity = distance * speed / vectorLen(distance);
    else
        velocity = sf::Vector2f(0, 0);
    Entity::update(dt);

}

