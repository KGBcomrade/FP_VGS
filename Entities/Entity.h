//
// Created by kgbcomrade on 4/29/20.
//

#ifndef FP2_ENTITY_H
#define FP2_ENTITY_H


#include <vector>
#include <level.h>

using namespace sf;

class Entity {
private:
    std::vector<Object> obj;
    Vector2f position, velocity, size;
    float speed, moveTimer;
    int health;
    bool life, isMove, onGround;
    Sprite sprite;
    String name;
public:
    Entity(Texture * texture, const String& name, Vector2f position, Vector2f size);
    FloatRect getRect();
    virtual void update(float dt);
};


#endif //FP2_ENTITY_H
