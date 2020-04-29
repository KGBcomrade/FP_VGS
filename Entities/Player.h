//
// Created by kgbcomrade on 4/29/20.
//

#ifndef FP2_PLAYER_H
#define FP2_PLAYER_H


#include <Misc/Level.h>
#include "Entity.h"

class Player : public Entity {
private:
    enum { left, right, up, down, jump, stay } state;//��������� ��� ������������ - ��������� �������
    int playerScore;
public:
    Player(sf::Texture * texture, const sf::String& name, sf::Vector2f position, sf::Vector2f size, Level &level);
    void control();
    void update(float dt) override;
};


#endif //FP2_PLAYER_H
