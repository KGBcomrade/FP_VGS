//
// Created by kgbcomrade on 4/29/20.
//

#ifndef FP2_ENTITY_H
#define FP2_ENTITY_H


#include <vector>
#include <Misc/Object.h>
#include <Misc/Level.h>


class Entity {
protected:
    std::vector<Object*> obj;
    sf::Vector2f position, velocity, size;

    float speed, moveTimer;
    int health;
    bool life, isMove, onGround;
    sf::Sprite *sprite;
    sf::String name;
public:
    Entity(sf::Texture * texture, const sf::String& name, sf::Vector2f position, sf::Vector2f size, Level & level);
    ~Entity();
    sf::FloatRect getRect();
    virtual void update(float dt);
    sf::Sprite *getSprite();
    void checkCollisionWithMap();

    sf::Vector2f getPosition();
};


#endif //FP2_ENTITY_H
