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
    if(vectorLen<float>(distance) > 30)
        if(distance.x != 0 && std::abs(distance.x) > std::abs(distance.y))
            velocity = sf::Vector2f(speed * (distance.x > 0 ? 1. : -1.), 0);
        else
            velocity = sf::Vector2f(0, speed * (distance.y > 0 ? 1. : -1.));

    else
        velocity = sf::Vector2f(0, 0);
    Entity::update(dt);

}

