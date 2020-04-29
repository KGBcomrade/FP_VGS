//
// Created by kgbcomrade on 4/29/20.
//

#include "Player.h"

void Player::control() {
    if (Keyboard::isKeyPressed) {//���� ������ �������
			if ((Keyboard::isKeyPressed(Keyboard::Left) || (Keyboard::isKeyPressed(Keyboard::A)))) {
				state = left;
			}
			if ((Keyboard::isKeyPressed(Keyboard::Right) || (Keyboard::isKeyPressed(Keyboard::D)))) {
				state = right;
			}
			if ((Keyboard::isKeyPressed(Keyboard::Up) || (Keyboard::isKeyPressed(Keyboard::W)))) {//���� ������ ������� ����� � �� �� �����, �� ����� �������
				state = up;
			}
			if ((Keyboard::isKeyPressed(Keyboard::Down) || (Keyboard::isKeyPressed(Keyboard::S)))) {
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

Player::Player(Texture *texture, const String &name, Vector2f position, Vector2f size, Level &level) : Entity::Entity(texture, name, position, size, level){
    playerScore = 0;
    state = stay;
    if(name == "Player1")
        sprite.setTextureRect(IntRect(4, 19, size.x, size.y));
}

