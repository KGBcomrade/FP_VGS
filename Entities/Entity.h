//
// Created by kgbcomrade on 4/29/20.
//

#ifndef FP2_ENTITY_H
#define FP2_ENTITY_H


#include <vector>
#include <level.h>

using namespace sf;

class Entity {
public:
    std::vector<Object> obj;
    Vector2f position, velocity, size;
    float speed, moveTimer;
    int health;
    bool life, isMove, onGround;
    Sprite sprite;
    String name;
    Entity(Texture * texture, const String& name, Vector2f position, Vector2f size);
    FloatRect getRect();
};


#endif //FP2_ENTITY_H
