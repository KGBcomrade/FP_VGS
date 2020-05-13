//
// Created by kgbcomrade on 4/29/20.
//

#include <Utils/Utils.h>

#include <utility>
#include <iostream>
#include "Enemy.h"

Enemy::Enemy(sf::Texture *texture, const sf::String &name, sf::Vector2f position, sf::Vector2f size, Level &level, Player* player1, std::string type1) : Entity(texture,
                                                                                                            name,
                                                                                                            position,
                                                                                                            size,
                                                                                                            level) {
    type = std::move(type1);
    player = player1;
    if(name == "EasyEnemy") {
        //sprite.setTextureRect(sf::IntRect(4, 19, size.x, size.y));
        velocity = sf::Vector2f(0, 0);
    }
    checked = false;
    speed = .1;

}

void Enemy::update(float dt) {
    if(!nodeStack.empty()) {

        sf::Vector2f currentGoal = nodeStack.top(), distance = currentGoal - position;

        if(vectorLen(distance) < .1) {
            position = currentGoal;
            nodeStack.pop();
            velocity *= 0.0f;
        }
        else if(distance.x != 0 && std::abs(distance.x) > std::abs(distance.y))
            velocity = sf::Vector2f(speed * (distance.x > 0 ? 1. : -1.), 0);
        else if(distance.y != 0)
            velocity = sf::Vector2f(0, speed * (distance.y > 0 ? 1. : -1.));


    }

    Entity::update(dt);

}

void Enemy::setNodeStack(std::stack<sf::Vector2f> stack) {
    nodeStack = std::move(stack);
}

sf::Vector2f Enemy::getCurrentGoal() {
    return nodeStack.empty() ? position : nodeStack.top();
}

void Enemy::setChecked() {
    checked = true;
}

bool Enemy::isChecked() {
    return checked;
}

std::string Enemy::getType() {
    return type;
}

