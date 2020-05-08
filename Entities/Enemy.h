//
// Created by kgbcomrade on 4/29/20.
//

#ifndef FP2_ENEMY_H
#define FP2_ENEMY_H


#include "Entity.h"
#include "Player.h"

class Enemy : public Entity{
protected:
    std::stack<sf::Vector2f> nodeStack;
    Player *player;
public:
    Enemy(sf::Texture * texture, const sf::String& name, sf::Vector2f position, sf::Vector2f size, Level & level, Player* player1);
    void setNodeStack(std::stack<sf::Vector2f> stack);
    void update(float dt) override;
    sf::Vector2f getCurrentGoal();
};


#endif //FP2_ENEMY_H
