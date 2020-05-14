//
// Created by kgbcomrade on 4/29/20.
//

#include <SFML/Window/Keyboard.hpp>
#include "Player.h"

void Player::control() {
    if (sf::Keyboard::isKeyPressed) {//���� ������ �������
			if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || (sf::Keyboard::isKeyPressed(sf::Keyboard::A)))) {
				state = left;
			}
			else if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || (sf::Keyboard::isKeyPressed(sf::Keyboard::D)))) {
				state = right;
			}
			else if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || (sf::Keyboard::isKeyPressed(sf::Keyboard::W)))) {//���� ������ ������� ����� � �� �� �����, �� ����� �������
				state = up;
			}
			else if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Down) || (sf::Keyboard::isKeyPressed(sf::Keyboard::S)))) {
				state = down;
			}
			else
			    state = stay;
		}

}

void Player::update(float dt){
    Entity::update(dt);
    control();
    switch (state) {
        case right:
            velocity.x = speed;
            velocity.y = 0;
            break;
        case left:
            velocity.x = -speed;
            velocity.y = 0;
            break;
        case up:
            velocity.x = 0;
            velocity.y = -speed;
            break;
        case down:
            velocity.x = 0;
            velocity.y = speed;
            break;
        case stay:
            velocity.x = velocity.y = 0;
            break;
    }
    state = stay;
}

Player::Player(sf::Texture *texture, const sf::String &name, sf::Vector2f position, sf::Vector2f size, Level &level) : Entity::Entity(texture, name, position, size, level){
    playerScore = 0;
    health = 3;
    state = stay;
    if(name == "Player1")
        sprite->setTextureRect(sf::IntRect(4, 19, size.x, size.y));
}

int Player::getHealth() {
    return health;
}

bool Player::isAlive() {
    return health > 0;
}

void Player::damage(int damage) {
    health -= damage;
}

void Player::incrementScore() {
    playerScore++;
}

int Player::getScore() {
    return playerScore;
}

