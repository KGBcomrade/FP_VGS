//
// Created by kgbcomrade on 4/29/20.
//

#include "Enemy.h"

Enemy::Enemy(Texture *texture, const String &name, Vector2f position, Vector2f size, Level &level) : Entity(texture,
                                                                                                            name,
                                                                                                            position,
                                                                                                            size,
                                                                                                            level) {
    if(name == "EasyEnemy") {
        sprite.setTextureRect(IntRect(position.x, position.y, position.x + size.x, position.y + size.y));
        velocity = Vector2f(.2, 0);
    }

}

