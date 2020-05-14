//
// Created by kgbcomrade on 4/29/20.
//

#ifndef FP2_PLAYER_H
#define FP2_PLAYER_H


#include <Misc/Level.h>
#include "Entity.h"

class Player : public Entity {
private:
    int health;
    enum { left, right, up, down, jump, stay } state;//��������� ��� ������������ - ��������� �������
    int playerScore;
public:
    Player(sf::Texture * texture, const sf::String& name, sf::Vector2f position, sf::Vector2f size, Level &level);
    void control();
    void update(float dt) override;
    int getHealth();
    ///@returns true if health >= 0
    bool isAlive();
    /**
     * Subtracts damage from health
     * @param damage subtrahend from health
     */
    void damage(int damage);
    ///Increments playerScore by 1
    void incrementScore();
    ///@returns playerScore
    int getScore();
};


#endif //FP2_PLAYER_H
