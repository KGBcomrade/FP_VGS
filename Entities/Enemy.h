//
// Created by kgbcomrade on 4/29/20.
//

#ifndef FP2_ENEMY_H
#define FP2_ENEMY_H


#include "Entity.h"

class Enemy : public Entity{
public:
    Enemy(Texture * texture, const String& name, Vector2f position, Vector2f size, Level & level);
};


#endif //FP2_ENEMY_H
