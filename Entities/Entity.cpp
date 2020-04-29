//
// Created by kgbcomrade on 4/29/20.
//

#include "Entity.h"

Entity::Entity(Texture * texture, const String &name, Vector2f position, Vector2f size)  {
    this->name = name;
    this->position = position;
    this->size = size;
    sprite = Sprite(*texture);
}

FloatRect Entity::getRect() {
    return FloatRect(position, size);
}





