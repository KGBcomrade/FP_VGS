//
// Created by kgbcomrade on 4/29/20.
//

#ifndef FP2_ENTITY_H
#define FP2_ENTITY_H


#include <vector>
#include <Misc/Object.h>
#include <Misc/Level.h>

using namespace sf;

class Entity {
protected:
    std::vector<Object> obj;
    Vector2f position, velocity, size;
    float speed, moveTimer;
    int health;
    bool life, isMove, onGround;
    Sprite sprite;
    String name;
public:
    Entity(Texture * texture, const String& name, Vector2f position, Vector2f size, Level & level);
    FloatRect getRect();
    virtual void update(float dt);

    void checkCollisionWithMap(Vector2f dvec);
};


#endif //FP2_ENTITY_H
