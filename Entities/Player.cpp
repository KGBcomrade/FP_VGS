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
			if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || (sf::Keyboard::isKeyPressed(sf::Keyboard::D)))) {
				state = right;
			}
			if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || (sf::Keyboard::isKeyPressed(sf::Keyboard::W)))) {//���� ������ ������� ����� � �� �� �����, �� ����� �������
				state = up;
			}
			if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Down) || (sf::Keyboard::isKeyPressed(sf::Keyboard::S)))) {
				state = down;
			}
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
            velocity.y = speed;
            break;
        case down:
            velocity.x = 0;
            velocity.y = -speed;
            break;
        case stay:
            velocity.x = velocity.y = 0;
            break;
    }
}

Player::Player(sf::Texture *texture, const sf::String &name, sf::Vector2f position, sf::Vector2f size, Level &level) : Entity::Entity(texture, name, position, size, level){
    playerScore = 0;
    state = stay;
    if(name == "Player1")
        sprite.setTextureRect(sf::IntRect(4, 19, size.x, size.y));
}

